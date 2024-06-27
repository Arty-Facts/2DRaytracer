#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "Ray.h"
#include "Vec2.h"
#include <iostream>

template <typename T>
class Camera {
public:
    Vec2<T> position;
    Vec2<T> direction;
    std::vector<Ray<T>> rays;
    float fov;
    int numRays;
    int currentRay = 0;

    Camera(const Vec2<T>& position,  const Vec2<T>& direction, float fov, int numRays)
        : position(position), direction(direction), fov(fov), numRays(numRays) {}

    Ray<T>& getRay() {
        if (numRays >= rays.size()) {
            rays.emplace_back();
        }

        if (currentRay >= rays.size()) {
            currentRay = 0;
        }
        return rays[currentRay++];
    } 

    Ray<T>& generateRay() {
        Ray<T>& ray = getRay();
        float fromAngle = fov / 2.0f;
        float toAngle = - fov / 2.0f;

        float angle = fromAngle + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (toAngle - fromAngle)));
        ray.origin = position;
        ray.direction = direction.rotate(angle);
        return ray;
    }
};

#endif // CAMERA_H
