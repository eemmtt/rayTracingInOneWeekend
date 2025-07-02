#include "rtweekend.h"
#include "rgb.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "interval.h"
#include "camera.h"

using namespace std;
int main(){
    hittable_list world;

    world.add(make_shared<sphere>(pt3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(pt3(0,-100.5,-1), 100));

    camera cam;

    cam.ASPECT_RATIO = 16.0 / 9.0;
    cam.img_width = 400;

    cam.render(world);
}