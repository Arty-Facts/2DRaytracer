#ifndef RAY_H
#define RAY_H

#include "Vec2.h"
#include <SFML/Graphics.hpp>

template <typename T>
class Ray {
public:
    Vec2<T> origin;
    Vec2<T> direction;
    sf::Color color;

    Ray(const Vec2<T>& origin, const Vec2<T>& direction, sf::Color color = sf::Color::White)
        : origin(origin), direction(direction.normalize()), color(color) {}

    void draw(sf::RenderWindow& window, const Vec2<T>& end) const {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(origin.x, origin.y), color),
            sf::Vertex(sf::Vector2f(end.x, end.y), color)
        };
        window.draw(line, 2, sf::Lines);
    }
};

#endif // RAY_H
