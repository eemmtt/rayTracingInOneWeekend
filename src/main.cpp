#include "rtweekend.h"
#include "rgb.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "interval.h"

rgb ray_rgb(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.N + rgb(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    double a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * rgb(1.0, 1.0, 1.0) + a * rgb(0.5, 0.7, 1.0);
}

using namespace std;
int main(){

    // Image

    double ASPECT_RATIO = 4.0 / 3.0;
    int img_width = 400;
    int img_height = int(img_width / ASPECT_RATIO);
    img_height = img_height < 1? 1 : img_height;

    // World

    hittable_list world;

    world.add(make_shared<sphere>(pt3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(pt3(0,-100.5,-1), 100));


    // Camera

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (double(img_width)/img_height);
    pt3 camera_orig = pt3(0,0,0);

    // viewport bases
    vec3 viewport_u = vec3(viewport_width,0,0);
    vec3 viewport_v = vec3(0,-viewport_height,0);

    //pixel bases
    vec3 pixel_dU = viewport_u / img_width;
    vec3 pixel_dV = viewport_v / img_height;

    // top left corner of viewport rect
    pt3 viewport_orig = camera_orig - vec3(0,0,focal_length) - (viewport_u / 2) - (viewport_v / 2);
    
    // center of top left pixel
    pt3 pixel00_pos = viewport_orig + 0.5 * (pixel_dU + pixel_dV);


    // Render

    cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for (int y = 0; y < img_height; y++){
        clog << "\rScanlines remaining: " << (img_height - y) << ' ' << flush;
        for (int x = 0; x < img_width; x++){
            pt3 pixel_center = pixel00_pos + (x * pixel_dU) + (y * pixel_dV);
            vec3 ray_dir = pixel_center - camera_orig;
            ray r(camera_orig, ray_dir);

            rgb pixel_rgb = ray_rgb(r, world);
            write_rgb(cout, pixel_rgb);
        }
    }

    clog << "\rDone.                \n";
}