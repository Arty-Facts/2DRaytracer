#ifndef VEC2_H
#define VEC2_H

#include <cmath>

template <typename T>
class Vec2 {
public:
    T x, y;

    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}

    Vec2<T> operator+(const Vec2<T>& other) const {
        return Vec2<T>(x + other.x, y + other.y);
    }

    Vec2<T> operator-(const Vec2<T>& other) const {
        return Vec2<T>(x - other.x, y - other.y);
    }

    Vec2<T> operator*(T scalar) const {
        return Vec2<T>(x * scalar, y * scalar);
    }

    T dot(const Vec2<T>& other) const {
        return x * other.x + y * other.y;
    }

    T length() const {
        return std::sqrt(x * x + y * y);
    }

    Vec2<T> normalize() const {
        T len = length();
        return Vec2<T>(x / len, y / len);
    }
};

#endif // VEC2_H
