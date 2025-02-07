//#include "rtweekend.h"

#include "constants.h"

#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

#include "camera.h"
#include "Presets.h"

#include <iostream>


int main() {
    camera cam(Presets::CreateSettings(3));
    cam.render(Presets::CreateWorld(3));
}