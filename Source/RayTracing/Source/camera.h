#pragma once

#include "hittable.h"
#include "material.h"

#include "RTImage.h"

#include <fstream>
#include <opencv2/opencv.hpp>


#include "ThreadPool.h"
#include "RTThread.h"

class Command;
#include "RenderSettings.h"

class camera {
public:
    camera(const RenderSettings& Settings);

    const RenderSettings& SETTINGS;

    void DisplayRender();
    void ComputePixel(int i, int j, const hittable& world, Command* onFinish);
    void render(const hittable& world);
    

    

private:
    /* Private Camera Variables Here */
    int    image_height;   // Rendered image height
    double pixel_samples_scale;  // Color scale factor for a sum of pixel samplesdouble pixel_samples_scale;  // Color scale factor for a sum of pixel samples
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    vec3   u, v, w;              // Camera frame basis vectors
    vec3   defocus_disk_u;       // Defocus disk horizontal radius
    vec3   defocus_disk_v;       // Defocus disk vertical radius

    ThreadPool* pool;
    RTImage *CV_Image;

    void initialize();

    point3 defocus_disk_sample() const;
    color ray_color(const ray& r, int depth, const hittable& world) const;
    ray get_ray(int i, int j) const;
    vec3 sample_square() const;
};