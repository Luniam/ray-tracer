#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"

using std::shared_ptr;
using std::make_shared;
using std::vector;

class hittable_list : public hittable {

    public:
        hittable_list() {}
        hittable_list(shared_ptr<hittable> hittable_object) { add(hittable_object); }

        void clear() { hittable_objects.clear(); }
        void add(shared_ptr<hittable> hittable_object) {
            hittable_objects.push_back(hittable_object);
        }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        vector<shared_ptr<hittable>> hittable_objects;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for(const auto& hittable_object : hittable_objects) {
        if(hittable_object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}

#endif