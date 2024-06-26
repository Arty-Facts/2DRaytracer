#include <SFML/Graphics.hpp>
#include "Vec2.h"
#include "Ray.h"
#include "Camera.h"
#include "Object.h"
#include "Scene.h"
#include "IntersectResult.h"

const int WIDTH = 800;
const int HEIGHT = 600;
const int DEBUG_HEIGHT = 200;
const int NUM_RAYS = 100; // Number of rays
const int MAX_BOUNCES = 5;

void trace(const Ray<float>& ray, const Scene<float>& scene, sf::RenderWindow& mainWindow) {
    IntersectResult<float> result = scene.intersect(ray);

    if (result.hit) {
        ray.draw(mainWindow, result.hitLocation); // Draw ray up to the intersection point

        // Optionally: Draw a small circle at the intersection point
        sf::CircleShape intersectionMarker(2);
        intersectionMarker.setPosition(result.hitLocation.x - 2, result.hitLocation.y - 2);
        intersectionMarker.setFillColor(result.color);
        mainWindow.draw(intersectionMarker);
    }
    else
        ray.draw(mainWindow, ray.origin - ray.direction * 200.0f); // Draw ray up to 200 units
}

void drawCameraFOV(const Camera<float>& camera, sf::RenderWindow& debugWindow) {
    // Draw camera position
    sf::CircleShape cameraShape(5);
    cameraShape.setPosition(camera.position.x - 5, camera.position.y - 5);
    cameraShape.setFillColor(sf::Color::Green);
    debugWindow.draw(cameraShape);

    // Draw FOV lines
    float angleStep = camera.fov / 2.0f;
    float startAngle = -camera.fov / 2.0f;
    for (int i = 0; i <= 2; ++i) {
        float angle = startAngle + i * angleStep;
        float radian = angle * (3.14159265 / 180.0f);
        Vec2<float> direction(std::cos(radian), std::sin(radian));
        Vec2<float> end = camera.position - direction * 200.0f;

        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(camera.position.x, camera.position.y), sf::Color::Green),
            sf::Vertex(sf::Vector2f(end.x, end.y), sf::Color::Green)
        };
        debugWindow.draw(line, 2, sf::Lines);
    }
}

int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(WIDTH, HEIGHT), "2D Path Tracer");
    sf::RenderWindow debugWindow(sf::VideoMode(WIDTH, DEBUG_HEIGHT), "Debug View");

    Camera<float> camera(Vec2<float>(400.f, 300.f), 90.f, NUM_RAYS);
    Scene<float> scene;

    // Add objects to the scene
    Circle<float> circle1(Vec2<float>(200.f, 400.f), 50.f, sf::Color::Red);
    Circle<float> circle2(Vec2<float>(100.f, 200.f), 50.f, sf::Color::Blue);
    scene.addObject(&circle1);
    scene.addObject(&circle2);

    while (mainWindow.isOpen() && debugWindow.isOpen()) {
        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
        }

        while (debugWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                debugWindow.close();
        }

        // mainWindow.clear(sf::Color::Black);
        debugWindow.clear(sf::Color::Black);

        // Draw the scene objects in the debug window
        for (const auto& object : scene.objects) {
            if (auto circle = dynamic_cast<Circle<float>*>(object)) {
                sf::CircleShape shape(circle->radius);
                shape.setPosition(circle->center.x - circle->radius, circle->center.y - circle->radius);
                shape.setFillColor(circle->color);
                debugWindow.draw(shape);
            }
        }

        // Draw camera and its FOV in the debug window
        drawCameraFOV(camera, debugWindow);

        auto rays = camera.generateRays();
        for (const auto& ray : rays) {
            trace(ray, scene, mainWindow);
        }

        mainWindow.display();
        debugWindow.display();
    }

    return 0;
}
