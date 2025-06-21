#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>

#include "hittable.h"
#include "vec3.h"
#include "ray.h"
#include "interval.h"

class sphere : public hittable {
    public:
        sphere(const pt3& center, double radius) : center(center), radius (std::fmax(0,radius)) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            double a = r.direction().length_squared();
            double h = dot(r.direction(), oc);
            double c = oc.length_squared() - radius * radius;

            double  discriminant = h*h - a*c;
            if (discriminant < 0) {
                return false;
            }
            
            //if + or - the root is outside range, return false early
            double sqrtd = std::sqrt(discriminant);
            double root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)){
                root = (h + sqrtd) / a;
                if (!ray_t.surrounds(root)){
                    return false;
                }
            }

            //update passed hit record
            rec.t = root;
            rec.pt = r.at(rec.t);
            vec3 outward_normal = (rec.pt - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }


    private:
        pt3 center;
        double radius;
};

#endif