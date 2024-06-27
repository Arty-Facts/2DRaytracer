#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "IntersectResult.h"

template <typename T>
class Object {
public:
    virtual IntersectResult<T> intersect(const Ray<T>& ray) const = 0;
};

template <typename T>
class Circle : public Object<T> {
public:
    Vec2<T> center;
    T radius;
    sf::Color color;
    float radiance;
    bool emitter;

    Circle(const Vec2<T>& center, T radius, sf::Color color = sf::Color::White, bool emitter = false, T radiance = 0)
        : center(center), radius(radius), color(color), emitter(emitter), radiance(radiance) {}

    IntersectResult<T> intersect(const Ray<T>& ray) const override {
        IntersectResult<T> result;
        Vec2<T> oc = ray.origin - center;

        T a = ray.direction.dot(ray.direction);
        T b = 2.0 * oc.dot(ray.direction);
        T c = oc.dot(oc) - radius * radius;
        T discriminant = b * b - 4 * a * c;
        T t = (-b - std::sqrt(discriminant)) / (2.0 * a);
        if (discriminant < 0) {
            return result; // No intersection
        } else if (t < 0) {
            return result; // Behind the camera
        } else {
            result.hit = true;
            result.origin = ray.origin;
            result.hitLocation = ray.origin + ray.direction * t;
            result.distance = (ray.origin - result.hitLocation).length();
            result.normal = (result.hitLocation - center).normalize();
            result.color = color;
            float dotProduct = result.normal.normalize().dot(ray.direction.normalize());
            float dotProduct2 = result.normal.normalize().dot(-ray.direction.normalize());
            dotProduct = std::min(std::abs(dotProduct),std::abs(dotProduct2));
            result.intensity = std::max(0.0f,dotProduct);
            result.emitter = emitter;
            return result;
        }
    }
};

#endif // OBJECT_H
