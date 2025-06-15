#include "rgb.h"
#include "vec3.h"

#include <iostream>

using namespace std;
int main(){

    // Image

    int img_width = 256;
    int img_height = 256;

    // Render

    cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for (int y = 0; y < img_height; y++){
        clog << "\rScanlines remaining: " << (img_height - y) << ' ' << flush;
        for (int x = 0; x < img_width; x++){
            rgb pixel_rgb = rgb(double(x)/(img_width-1), double(y)/(img_height-1), 0);
            write_rgb(cout, pixel_rgb);
        }
    }

    clog << "\rDone.                \n";
}