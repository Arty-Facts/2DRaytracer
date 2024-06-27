#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>
#include "Vec2.h"

template <typename T>
class Line {
public:
    Vec2<T> start;
    Vec2<T> end;
    sf::Color color;
    T age;

    Line(const Vec2<T>& start=Vec2<float>(0, 0), const Vec2<T>& end=Vec2<float>(0, 0), const sf::Color& color= sf::Color::White)
        : start(start), end(end), color(color), age(0) {}

    void update(float deltaTime) {
        float reduce = deltaTime/age;
        
        int dimmingFactor = static_cast<int>(255 * reduce); // Adjust the dimming speed
        color.r = std::max(0, color.r - dimmingFactor);
        color.g = std::max(0, color.g - dimmingFactor);
        color.b = std::max(0, color.b - dimmingFactor);
        color.a = std::max(0, color.a - dimmingFactor);
    }

    void draw(sf::RenderWindow& window) const {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(start.x, start.y), color),
            sf::Vertex(sf::Vector2f(end.x, end.y), color)
        };
        window.draw(line, 2, sf::Lines);
    }
};

template <typename T>
class LineFILO{
public:
    std::vector<Line<T>> lines;
    int maxLines;
    int currentLine = 0;
    LineFILO(int maxLines) : maxLines(maxLines){}

    Line<T>& get_line(){
        if(currentLine >= maxLines){
            currentLine = 0;
        }
        if (lines.size() < maxLines){
            return lines.emplace_back();
        }
        return lines[currentLine++];
    }
    void update(T deltaTime){
        for(auto& line : lines){
            line.update(deltaTime);
        }
    }
    void draw(sf::RenderWindow& window){
        for(auto& line : lines){
            if (line.color.r < 1 && line.color.g < 1 && line.color.b < 1){
                continue;
            }
            line.draw(window);
        }
    }
};

#endif // LINE_H
