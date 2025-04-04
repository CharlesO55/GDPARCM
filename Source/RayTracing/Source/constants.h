#pragma once
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>


// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// Utility Functions

inline double random_double() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}