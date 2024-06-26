#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "Ray.h"
#include "Vec2.h"

template <typename T>
class Camera {
public:
    Vec2<T> position;
    float fov;
    int numRays;

    Camera(const Vec2<T>& position, float fov, int numRays)
        : position(position), fov(fov), numRays(numRays) {}

    std::vector<Ray<T>> generateRays() const {
        std::vector<Ray<T>> rays;
        float angleStep = fov / static_cast<float>(numRays);
        float startAngle = -fov / 2.0f;

        for (int i = 0; i < numRays; ++i) {
            float angle = startAngle + i * angleStep;
            float radian = angle * (3.14159265 / 180.0f);
            Vec2<T> direction(std::cos(radian), std::sin(radian));
            rays.emplace_back(position, direction);
        }
        return rays;
    }
};

#endif // CAMERA_H
