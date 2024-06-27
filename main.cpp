#include <SFML/Graphics.hpp>
#include "Vec2.h"
#include "Ray.h"
#include "Camera.h"
#include "Object.h"
#include "Scene.h"
#include "IntersectResult.h"
#include "Line.h"
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 600;
const int DEBUG_HEIGHT = 200;
const int NUM_RAYS = 1000; // Number of rays
const int MAX_BOUNCES = 5;
const float TURN_SPEED = 50.0f;
const float MOVE_SPEED = 100.0f;
const float AGE_SPEED = 1.0f;
const float ALPHA = 1.0f;
const int HISTOGRAM_HEIGHT = 100;
const int HISTOGRAM_BINS = 100;

template <typename T>
Vec2<T> scatter(Vec2<T>& normal) {
    // Simple diffuse scatter
    float fromAngle = -90.0f;
    float toAngle = 90.0f;
    float angle = fromAngle + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (toAngle - fromAngle)));
    return normal.rotate(angle);
}


sf::Color blend(const sf::Color& income, const sf::Color& obj, float intensity) {
    sf::Color out;
    out.r = obj.r * intensity * (income.r / 255.0f);
    out.g = obj.g * intensity * (income.g / 255.0f);
    out.b = obj.b * intensity * (income.b / 255.0f);
    return out;
}


void trace(Ray<float>& ray, const Scene<float>& scene, LineFILO<float>& lines, sf::RenderWindow& mainWindow) {
    std::vector<IntersectResult<float>> results;
    for (int i = 0; i < MAX_BOUNCES; ++i) {
        IntersectResult<float> result = scene.intersect(ray);

        if (result.hit) {
            results.push_back(result);
            if (result.emitter) {
                break;
            }
            ray.origin = result.hitLocation;
            ray.direction = scatter(result.normal);
        } else {
            break;
        }

    }
    sf::Color color = sf::Color::Black;
    color.a = 100;
    for (auto result = results.rbegin(); result != results.rend(); ++result){
        if (result->emitter) {
            color = result->color;
        }
        if (result->color.r < 1 && result->color.g < 1 && result->color.b < 1){
            break;
        }
        Line<float>& line = lines.get_line();
        line.start = result->origin;
        line.end = result->hitLocation;
        color = blend(color, result->color, result->intensity);
        line.color = color;
        line.age = AGE_SPEED;

    }
}

void drawCameraFOV(const Camera<float>& camera, sf::RenderWindow& debugWindow) {
    // Draw camera position
    sf::CircleShape cameraShape(6);
    cameraShape.setPosition(camera.position.x - 6, camera.position.y - 6);
    cameraShape.setFillColor(sf::Color::Green);
    debugWindow.draw(cameraShape);

    // Draw FOV lines
    float angleStep = camera.fov / static_cast<float>(NUM_RAYS);
    float startAngle = - camera.fov / 2.0f;
    sf::Color color = sf::Color::White;
    color.a = 10;

    for (int i = 0; i < NUM_RAYS; ++i) {
        float angle = startAngle + i * angleStep;
        Vec2<float> end = camera.position + camera.direction.rotate(angle) * 1000.0f;
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(camera.position.x, camera.position.y), color),
            sf::Vertex(sf::Vector2f(end.x, end.y), color)
        };
        debugWindow.draw(line, 2, sf::Lines);
    }
}

int main() {
    sf::RenderWindow mainWindow(sf::VideoMode(WIDTH, HEIGHT), "2D Path Tracer");
    sf::RenderWindow debugWindow(sf::VideoMode(WIDTH, DEBUG_HEIGHT), "Debug View");

    Camera<float> camera(Vec2<float>(400.f, 300.f), Vec2<float>(-1.f, 0.f), 90.f, NUM_RAYS);
    Scene<float> scene;

    LineFILO<float> lines(NUM_RAYS);


    // Add objects to the scene
    Circle<float> circle1(Vec2<float>(200.f, 350.f), 50.f, sf::Color::Red, false, ALPHA);
    Circle<float> circle2(Vec2<float>(250.f, 200.f), 30.f, sf::Color::Blue,false, ALPHA);
    Circle<float> circle3(Vec2<float>(350.f, 50.f), 40.f, sf::Color::Green,false, ALPHA);
    Circle<float> circle4(Vec2<float>(10.f, 200.f), 70.f, sf::Color::Cyan,false, ALPHA);
    Circle<float> light(Vec2<float>(100.f, 100.f), 20.f, sf::Color::White, true, 1.0f);

    scene.addObject(&circle1);
    scene.addObject(&circle2);
    scene.addObject(&circle3);
    scene.addObject(&circle4);
    scene.addObject(&light);

    
    sf::Clock clock; // Create a clock object to measure time

    while (mainWindow.isOpen() && debugWindow.isOpen()) {
        sf::Time elapsed = clock.restart(); // Restart the clock and get the elapsed time
        float deltaTime = elapsed.asSeconds(); // Convert the elapsed time to seconds

        sf::Event event;
        while (mainWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
        }

        while (debugWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                debugWindow.close();
        }

        mainWindow.clear(sf::Color::Black);
        debugWindow.clear(sf::Color::Black);

        // move the camera
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            camera.position += (camera.direction.normalize() + MOVE_SPEED) * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            camera.position -= (camera.direction.normalize() + MOVE_SPEED) * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camera.direction = camera.direction.rotate(-TURN_SPEED * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camera.direction = camera.direction.rotate(+TURN_SPEED * deltaTime);
        }



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


        Ray<float>& ray = camera.generateRay();
        trace(ray, scene, lines, mainWindow);
        std::vector<float> hitDistances;
        for (const auto& ray : camera.rays) {
            hitDistances.push_back(ray.radiance);
        }

        lines.update(deltaTime);
        lines.draw(mainWindow);

        mainWindow.display();
        debugWindow.display();
        sleep(sf::milliseconds(1));
    }

    return 0;
}
