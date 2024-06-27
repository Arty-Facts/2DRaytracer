#ifndef INTERSECTRESULT_H
#define INTERSECTRESULT_H

#include "Vec2.h"
#include <SFML/Graphics.hpp>

template <typename T>
class IntersectResult {
public:
    bool hit;
    T distance;
    Vec2<T> origin;
    Vec2<T> hitLocation;
    Vec2<T> normal;
    sf::Color color;
    float emitter;
    float intensity;

    IntersectResult()
        : hit(false), distance(std::numeric_limits<T>::max()), color(sf::Color::White), emitter(false), intensity(1) {}
};

#endif // INTERSECTRESULT_H
