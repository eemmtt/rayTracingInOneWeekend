#ifndef RGB_H
#define RGB_H

#include "vec3.h"

#include <iostream>

//tutorial calls this "color"
using rgb = vec3;

void write_rgb(std::ostream& out, const rgb& pixel_rgb) {
    double r = pixel_rgb.x();
    double g = pixel_rgb.y();
    double b = pixel_rgb.z();

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif