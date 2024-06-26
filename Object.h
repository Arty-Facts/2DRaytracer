#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "IntersectResult.h"

template <typename T>
class Object {
public:
    virtual IntersectResult<T> intersect(const Ray<T>& ray) const = 0;
    virtual Vec2<T> scatter(const Vec2<T>& normal) const = 0;
};

template <typename T>
class Circle : public Object<T> {
public:
    Vec2<T> center;
    T radius;
    sf::Color color;
    float emission;

    Circle(const Vec2<T>& center, T radius, sf::Color color = sf::Color::White, float emission = 0)
        : center(center), radius(radius), color(color), emission(emission) {}

    IntersectResult<T> intersect(const Ray<T>& ray) const override {
        IntersectResult<T> result;
        Vec2<T> oc = ray.origin - center;

        T a = ray.direction.dot(ray.direction);
        T b = 2.0 * oc.dot(ray.direction);
        T c = oc.dot(oc) - radius * radius;
        T discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return result; // No intersection
        } else {
            result.hit = true;
            result.hitLocation = ray.origin + ray.direction * ((-b + std::sqrt(discriminant)) / (2.0 * a));
            result.distance = (ray.origin - result.hitLocation).length();
            result.normal = (result.hitLocation - center).normalize();
            result.color = color;
            result.emission = emission;
            return result;
        }
    }

    Vec2<T> scatter(const Vec2<T>& normal) const override {
        // Simple diffuse scatter
        float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159265;
        return Vec2<T>(std::cos(angle), std::sin(angle)).normalize();
    }
};

#endif // OBJECT_H
