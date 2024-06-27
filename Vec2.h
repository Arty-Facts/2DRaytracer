#ifndef VEC2_H
#define VEC2_H

#include <cmath>

template <typename T>
class Vec2 {
public:
    T x, y;

    Vec2() : x(0), y(0) {}
    Vec2(T x, T y) : x(x), y(y) {}

    // Copy constructor
    Vec2(const Vec2<T>& other) : x(other.x), y(other.y) {}

    // Copy assignment
    Vec2<T>& operator=(const Vec2<T>& other) {
        x = other.x;
        y = other.y;
        return *this;
    }
    // Move constructor
    Vec2(Vec2<T>&& other) noexcept : x(other.x), y(other.y) {
        other.x = 0;
        other.y = 0;
    }

    // Move assignment
    Vec2<T>& operator=(Vec2<T>&& other) noexcept {
        x = other.x;
        y = other.y;
        other.x = 0;
        other.y = 0;
        return *this;
    }

    // Destructor
    ~Vec2() = default;

    bool operator==(const Vec2<T>& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vec2<T>& other) const {
        return x != other.x || y != other.y;
    }



    Vec2<T> operator+(const Vec2<T>& other) const {
        return Vec2<T>(x + other.x, y + other.y);
    }

    Vec2<T> operator-(const Vec2<T>& other) const {
        return Vec2<T>(x - other.x, y - other.y);
    }

    Vec2<T> operator-() const {
        return Vec2<T>(-x, -y);
    }

    Vec2<T> operator+(T other) const {
        return Vec2<T>(x * other, y * other);
    }

    Vec2<T> operator-(T other) const {
        return Vec2<T>(x - other, y - other);
    }

    Vec2<T> operator*( T other) const {
        return Vec2<T>(x * other, y * other);
    }

    Vec2<T> operator/(T other) const {
        return Vec2<T>(x / other, y / other);
    }



    Vec2<T> operator+=(const Vec2<T>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2<T> operator-=(const Vec2<T>& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2<T> operator*=(T other) {
        x *= other;
        y *= other;
        return *this;
    }

    Vec2<T> operator/=(T other) {
        x /= other;
        y /= other;
        return *this;
    }


    T dot(const Vec2<T>& other) const {
        return x * other.x + y * other.y;
    }

    T length() const {
        return std::sqrt(x * x + y * y);
    }

    T angle() const {
        return std::atan2(y, x);
    }

    Vec2<T> rotate(T angle) const {
        angle =  angle * 3.14159265 / 180;
        T newX = x * std::cos(angle) - y * std::sin(angle);
        T newY = x * std::sin(angle) + y * std::cos(angle);
        return Vec2<T>(newX, newY);
    }

    Vec2<T> normalize() const {
        T len = length();
        return Vec2<T>(x / len, y / len);
    }
};

#endif // VEC2_H
