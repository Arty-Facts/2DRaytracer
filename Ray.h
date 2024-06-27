#ifndef RAY_H
#define RAY_H

#include "Vec2.h"
#include <SFML/Graphics.hpp>

template <typename T>
class Ray {
public:
    Vec2<T> origin;
    Vec2<T> direction;
    T radiance;

    Ray(const Vec2<T>& origin = Vec2<T>(), const Vec2<T>& direction = Vec2<T>(1, 0))
        : origin(origin), direction(direction.normalize()), radiance(0) {}

    void draw(sf::RenderWindow& window, const Vec2<T>& end, const sf::Color& color = sf::Color::Black) const {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(origin.x, origin.y), color),
            sf::Vertex(sf::Vector2f(end.x, end.y), color),
        };
        window.draw(line, 2, sf::Lines);
    }
};

#endif // RAY_H
