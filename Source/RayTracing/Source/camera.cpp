#include "camera.h"

#include "Command.h"
#include "RTParams.h"

camera::camera(const RenderSettings& Settings) : SETTINGS(Settings)
{
}

void camera::DisplayRender() {
    while (true) {
        cv::imshow("Render", *CV_Image->getBGRChannel()->get());
        if (cv::waitKey(1000) > 0) {
            cv::destroyAllWindows();
            break;
        }
    }
}

void camera::ComputePixel(int i, int j, const hittable& world, Command* onFinish) {
    color pixel_color(0, 0, 0);
    for (int sample = 0; sample < SETTINGS.samples_per_pixel; sample++) {
        ray r = get_ray(i, j);
        pixel_color += ray_color(r, SETTINGS.max_depth, world);
    }

    //PNG
    color curr_pixel_values = output_color(pixel_samples_scale * pixel_color);
    CV_Image->setPixel(i, j, (float)curr_pixel_values.x(), (float)curr_pixel_values.y(), (float)curr_pixel_values.z(), SETTINGS.samples_per_pixel);


    onFinish->Execute();
}


#if RENDER_AS_PPM
void camera::render(const hittable& world) {
    std::ofstream file("Renders/PPM_Output.ppm");
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    initialize();

    file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }

            //PPM OUTPUT
            write_color(file, pixel_samples_scale * pixel_color);
        }
    }

    file.close();

    std::clog << "\rDone.                 \n";
}
#else

void camera::render(const hittable& world) {
    initialize();

    pool = new ThreadPool(*this, world);
    pool->InitThreadList(SETTINGS.Threads);

    CV_Image = new RTImage(SETTINGS.image_width, image_height);
    std::thread thread_Display(&camera::DisplayRender, this);


    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < SETTINGS.image_width; i++) {
            //ComputePixel(i, j, world);
            pool->Add(RTParams(i, j));
        }
    }
    pool->StartProcessing();

    thread_Display.join();
    
    pool->Stop();

    std::clog << "\rDone.                 \n";
    cv::String PNG_filename = "Renders/PNG_Output.png";
    CV_Image->saveImage(PNG_filename);
}
#endif // RENDER_AS_PPM
















#pragma region PRIVATES
void camera::initialize() {
    image_height = int(SETTINGS.image_width / SETTINGS.aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / SETTINGS.samples_per_pixel;

    center = SETTINGS.lookfrom;

    // Determine viewport dimensions.
    //center = point3(0, 0, 0);
    //auto focal_length = 1.0;
    //auto viewport_height = 2.0;

    //auto focal_length = (lookfrom - lookat).length();
    auto theta = degrees_to_radians(SETTINGS.vfov);
    auto h = std::tan(theta / 2);
    //auto viewport_height = 2 * h * focal_length;

    auto viewport_height = 2 * h * SETTINGS.focus_dist;
    auto viewport_width = viewport_height * (double(SETTINGS.image_width) / image_height);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = unit_vector(SETTINGS.lookfrom - SETTINGS.lookat);
    u = unit_vector(cross(SETTINGS.vup, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
    vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge


    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / SETTINGS.image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = center - (SETTINGS.focus_dist * w) - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Calculate the camera defocus disk basis vectors.
    auto defocus_radius = SETTINGS.focus_dist * std::tan(degrees_to_radians(SETTINGS.defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

point3 camera::defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk.
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}

color camera::ray_color(const ray& r, int depth, const hittable& world) const {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);

    hit_record rec;

    if (world.hit(r, interval(0.001, infinity), rec)) {
        //NORMAL COLOR
        //return 0.5 * (rec.normal + color(1, 1, 1));

        //UNIFORM SCATTERING
        //vec3 direction = random_on_hemisphere(rec.normal);

        //LAMBERTIAN
        /*vec3 direction = rec.normal + random_unit_vector();
        float gamma = 0.5f; //0.5f;
        return gamma * ray_color(ray(rec.p, direction), depth - 1, world);*/

        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, depth - 1, world);
        return color(0, 0, 0);
    }



    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

ray camera::get_ray(int i, int j) const {
    // Construct a camera ray originating from the origin and directed at randomly sampled
    // point around the pixel location i, j.

    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
        + ((i + offset.x()) * pixel_delta_u)
        + ((j + offset.y()) * pixel_delta_v);

    //auto ray_origin = center;

    // Construct a camera ray originating from the defocus disk and directed at a randomly
    // sampled point around the pixel location i, j.
    auto ray_origin = (SETTINGS.defocus_angle <= 0) ? center : defocus_disk_sample();

    auto ray_direction = pixel_sample - ray_origin;
    return ray(ray_origin, ray_direction);
}

vec3 camera::sample_square() const {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
}
#pragma endregion
