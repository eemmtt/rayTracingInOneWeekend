#include "rgb.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

double hit_sphere(const pt3& sph_center, double sph_radius, const ray& r) {
    vec3 oc = sph_center - r.origin();
    double a = r.direction().length_squared();
    double h = dot(r.direction(), oc);
    double c = oc.length_squared() - sph_radius * sph_radius;
    double  discriminant = h*h - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (h - std::sqrt(discriminant)) / (a);
    }
}

rgb ray_rgb(const ray& r) {
    // rgb componenet values are 0 - 1
    double t = hit_sphere(pt3(0,0,-1), 0.5, r);
    if (t > 0.0){
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5 * rgb(N.x() + 1, N.y() + 1, N.z() + 1);
    }

    vec3 unit_dir = unit_vector(r.direction());
    double a = 0.5*(unit_dir.y() + 1.0);
    return (1.0 - a) * rgb(1.0, 1.0, 1.0) + a * rgb(0.5, 0.65, 1.0);
}

using namespace std;
int main(){

    // Image

    double ASPECT_RATIO = 4.0 / 3.0;
    int img_width = 400;
    int img_height = int(img_width / ASPECT_RATIO);
    img_height = img_height < 1? 1 : img_height;

    // Camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(img_width)/img_height);
    pt3 camera_orig = pt3(0,0,0);

    vec3 viewport_u = vec3(viewport_width,0,0);
    vec3 viewport_v = vec3(0,-viewport_height,0);

    vec3 pixel_dU = viewport_u / img_width;
    vec3 pixel_dV = viewport_v / img_height;

    pt3 viewport_orig = camera_orig - vec3(0,0,focal_length) - (viewport_u / 2) - (viewport_v / 2);
    pt3 pixel00_pos = viewport_orig + 0.5 * (pixel_dU + pixel_dV);


    // Render

    cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for (int y = 0; y < img_height; y++){
        clog << "\rScanlines remaining: " << (img_height - y) << ' ' << flush;
        for (int x = 0; x < img_width; x++){
            pt3 pixel_center = pixel00_pos + (x * pixel_dU) + (y * pixel_dV);
            vec3 ray_dir = pixel_center - camera_orig;
            ray r(camera_orig, ray_dir);

            rgb pixel_rgb = ray_rgb(r);
            write_rgb(cout, pixel_rgb);
        }
    }

    clog << "\rDone.                \n";
}