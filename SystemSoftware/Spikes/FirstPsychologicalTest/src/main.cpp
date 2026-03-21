#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

using sf::Color;
using sf::CircleShape;
using sf::Event;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Clock;

bool started = false;
bool pressed = false;

std::int32_t real_time_elapsed = 0;
std::int32_t game_time_elapsed = 0;

struct Point {
    float x;
    float y;
};

class Path {
    public:
        struct Point P0;
        struct Point P1;
        void generatePath(float car_x, float car_y, float screen_x) {
            P0.x = 300;
            P0.y = 300;
            P1.x = screen_x;
            P1.y = 300;
        }
};

class Car {
    public:
        float actual_x;
        float actual_y;
        float x;
        float y;
        float t = 0;
        sf::RectangleShape shape;
        void moveAlongPath(struct Path *path, float screen_x) {
            float vel = path->P1.x - path->P0.y;
            float next_x = path->P0.x + vel*t;
            float next_dx = next_x-actual_x;
            t = t + 0.005;
            move(screen_x, next_dx);
        }

        void move(float screen_x, float dx) {
            actual_x += dx;
            if (actual_x > screen_x) {
                x = screen_x-20;
            } else if (actual_x < 0) {
                x = 20;
            } else {
                x = actual_x;
            }
            shape.setPosition(sf::Vector2f(x, 300));
        }
};

sf::RectangleShape initShape(int pos_x, int pos_y) {
    sf::RectangleShape shape(sf::Vector2f(20.0f, 20.0f));
    shape.setPosition(sf::Vector2f(pos_x,pos_y));
    return shape;
}

sf::RectangleShape initShape(int pos_x, int pos_y, float size_x, float size_y) {
    sf::RectangleShape shape(sf::Vector2f(size_x, size_y));
    shape.setPosition(sf::Vector2f(pos_x,pos_y));
    return shape;
}

Car initCar(int car_x, int car_y) {
    Car car;
    car.x = car_x;
    car.y = car_y;
    car.actual_x = car.x;
    car.actual_y = car.y;
    car.shape = initShape(car.x, car.y);
    return car;
}

/*Update method*/

int main() {
    RenderWindow window(VideoMode({600, 600}), "Test1");
    Car car;
    sf::RectangleShape wall;
    Path path;
    sf::Clock clock;
    if (!started) {
        car = initCar(300.0f, 300.0f);
        wall = initShape(450,250, 120.0f, 120.0f);
        started = true;
        path.generatePath(car.x, car.y, 600);
    }

    while (window.isOpen()) {
        while (clock.getElapsedTime().asMilliseconds() < 16) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<Event::Closed>()) {
                    window.close();
                }
            }
        }
        real_time_elapsed += clock.restart().asMilliseconds();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !pressed){
            printf("Position of t: %f\n", car.t);
            printf("Real time elapsed: %d\n", real_time_elapsed);
            printf("Game time elapsed: %d\n", game_time_elapsed);
            pressed = true;
            exit(0);
        }
        window.clear(Color::Blue);
        car.moveAlongPath(&path, 600);
        window.draw(car.shape);
        window.draw(wall);
        window.display();
        game_time_elapsed += clock.getElapsedTime().asMilliseconds();
        real_time_elapsed += clock.getElapsedTime().asMilliseconds();
    }
}