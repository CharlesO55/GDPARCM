#include "Presets.h"

#include "material.h"
#include "sphere.h"

#include <random>

RenderSettings Presets::CreateSettings(int ID)
{
    RenderSettings Settings;
    Settings.aspect_ratio = 16.0 / 9.0;
    Settings.image_width = 400;
    Settings.samples_per_pixel = 300;
    Settings.max_depth = 20;

    Settings.vfov = 20;
    Settings.lookfrom = point3(13, 2, 3);
    Settings.lookat = point3(0, 0, 0);
    Settings.vup = vec3(0, 1, 0);

    Settings.defocus_angle = 0.01;
    Settings.focus_dist = 10.0;

    Settings.Threads = 4;

    switch (ID) {
    case 2:
        Settings.defocus_angle = 3;
        Settings.focus_dist = 6;
        break;
    case 3:
        Settings.lookat = point3(0, 1, 0);
        break;
    default:
        break;
    }

    return Settings;
}

hittable_list Presets::CreateWorld(int ID)
{
    // GROUND
    hittable_list world;

    auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));



    switch (ID)
    {
    case 1:
    case 2:
        CreateSmallSpheres(world);
        CreateBigSpheres(world);
        break;
    case 3:
        CreateStackedSpheres(world);
        break;
    default:
        break;
    }
    return world;
}

void Presets::CreateSmallSpheres(hittable_list& world)
{
    double radius = 0.2;

    // 20x5 grid = 100 spheres
    int Zmin = -14;
    int Zmax = Zmin + 20;
    int Xmin = 0;
    int Xmax = Xmin + 5;

    for (int a = Zmin; a < Zmax; a++) {
        for (int b = Xmin; b < Xmax; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9 * random_double(), radius, b + random_double());

            if ((center - point3(4, radius, 0)).length() > 0.9) {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.94) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.97) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
                else {
                    // transparent glass
                    sphere_material = std::make_shared<dielectric>(1);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
}

void Presets::CreateBigSpheres(hittable_list& world)
{
    auto mat_Opaque0 = std::make_shared<lambertian>(color::random());
    auto mat_Opaque1 = std::make_shared<lambertian>(color(1, 0.8, 0));

    auto mat_RefractiveGlass = std::make_shared<dielectric>(2);
    auto mat_Metal = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);

    world.add(make_shared<sphere>(point3(-4, 1.5, -2), 1.5, mat_Opaque0));
    world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, mat_RefractiveGlass));
    world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, mat_Metal));
    world.add(make_shared<sphere>(point3(8, 1, 0), 1.0, mat_Opaque1));
}

void Presets::CreateStackedSpheres(hittable_list& world)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(6, 8);

    double radius = 0.2;
    for (int i = 1; i < distrib(gen); i++) {
        auto mat_Random = std::make_shared<lambertian>(color::random());
        world.add(make_shared<sphere>(vec3(0, i * 2 * radius, 0), radius, mat_Random));
    }

    auto mat_Random = std::make_shared<lambertian>(color(1,0.8,0));
    world.add(make_shared<sphere>(vec3(0, radius, radius), radius, mat_Random));
    world.add(make_shared<sphere>(vec3(0, radius, -radius), radius, mat_Random));
}