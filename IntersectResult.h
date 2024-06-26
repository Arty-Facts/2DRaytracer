#ifndef INTERSECTRESULT_H
#define INTERSECTRESULT_H

#include "Vec2.h"
#include <SFML/Graphics.hpp>

template <typename T>
class IntersectResult {
public:
    bool hit;
    T distance;
    Vec2<T> hitLocation;
    Vec2<T> normal;
    sf::Color color;
    float emission;

    IntersectResult()
        : hit(false), distance(0), color(sf::Color::White), emission(0) {}
};

#endif // INTERSECTRESULT_H
