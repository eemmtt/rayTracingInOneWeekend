#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "interval.h"

class hit_record {
    public:
        pt3 pt;
        vec3 N;
        double t;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outward_normal){
            //outward_normal assumed to have unit length
            front_face = dot(r.direction(), outward_normal) < 0;

            // N always points towards the camera
            N = front_face ? outward_normal : -outward_normal;
        }
};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

#endif