#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Object.h"
#include "IntersectResult.h"

template <typename T>
class Scene {
public:
    std::vector<Object<T>*> objects;

    void addObject(Object<T>* object) {
        objects.push_back(object);
    }

    IntersectResult<T> intersect(const Ray<T>& ray) const {
        IntersectResult<T> closestResult;
        closestResult.hit = false;
        T closest_t = std::numeric_limits<T>::max();

        for (const auto& object : objects) {
            IntersectResult<T> result = object->intersect(ray);
            if (result.hit && result.distance < closest_t) {
                closest_t = result.distance;
                closestResult = result;
            }
        }
        return closestResult;
    }
};

#endif // SCENE_H
