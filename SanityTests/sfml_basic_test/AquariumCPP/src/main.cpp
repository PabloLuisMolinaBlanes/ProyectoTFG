#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

using sf::Color;
using sf::CircleShape;
using sf::Event;
using sf::RenderWindow;
using sf::VideoMode;

bool started = false;

struct Point {
    float x;
    float y;
};

class BezierCurve {
    public:
        struct Point P0;
        struct Point P1;
        struct Point P2;
        void generateBezierCurve(float fish_x, float fish_y, float screen_x, float screen_y) {
            Point P0_temp;
            Point P1_temp;
            Point P2_temp;
            P0_temp.x = fish_x;
            P0_temp.y = fish_y;
            P1_temp.x = roundf(((double)rand()/RAND_MAX)*screen_x);
            P1_temp.y = roundf(((double)rand()/RAND_MAX)*screen_y);
            P2_temp.x = roundf(((double)rand()/RAND_MAX)*screen_x);
            P2_temp.y = roundf(((double)rand()/RAND_MAX)*screen_y);
            P0 = P0_temp;
            P1 = P1_temp;
            P2 = P2_temp;
        }
};

class Fish {
    public:
        float actual_x;
        float actual_y;
        float x;
        float y;
        float t = 0;
        sf::RectangleShape shape;
        void moveAlongBezierCurve(struct BezierCurve *bezier, float screen_x, float screen_y) {
            if (t < 1) {
                float next_x = pow((1-t), 2)*bezier->P0.x + 2*(1-t)*t*bezier->P1.x + pow(t, 2)*bezier->P2.x;
		        float next_y = pow((1-t), 2)*bezier->P0.y + 2*(1-t)*t*bezier->P1.y + pow(t, 2)*bezier->P2.y;
		        float distanceToMoveX;
		        float directionX;
		        float distanceToMoveY;
		        float directionY;
                if (next_x < actual_x) {
			        distanceToMoveX = actual_x - next_x;
			        directionX = -1;
		        } else if (next_x > actual_x) {
			        distanceToMoveX = next_x - actual_x;
			        directionX = 1;
		        }
		        if (next_y < actual_y) {
			        distanceToMoveY = y - next_y;
			        directionY = -1;
		        } else if (next_y > actual_y) {
			        distanceToMoveY = next_y - actual_y;
			        directionY = 1;
		        }
		    float next_dx = directionX * distanceToMoveX;
		    float next_dy = directionY * distanceToMoveY;
            t = t + 0.0001;
            move(screen_x, screen_y, next_dx, next_dy);
            } else {
                t = 0;
                actual_x = x;
                actual_y = y;
                bezier->generateBezierCurve(x, y, screen_x, screen_y);
            }
        }
        void move(float screen_x, float screen_y, float dx, float dy) {
            actual_x += dx;
            actual_y += dy;
            if (actual_x > screen_x) {
                x = screen_x-20;
            } else if (actual_x < 0) {
                x = 20;
            } else {
                x = actual_x;
            }
            if (actual_y > screen_y) {
                y = screen_y-20;
            } else if (actual_y < 0) {
                y = 20;
            } else {
                y = actual_y;
            }
            shape.setPosition(sf::Vector2f(x, y));
        }
};

sf::RectangleShape initShape(int pos_x, int pos_y) {
    sf::RectangleShape shape(sf::Vector2f(20.0f, 20.0f));
    shape.setPosition(sf::Vector2f(pos_x,pos_y));
    return shape;
}

Fish initFish(int fish_x, int fish_y) {
    Fish fish;
    fish.x = fish_x;
    fish.y = fish_y;
    fish.actual_x = fish.x;
    fish.actual_y = fish.y;
    fish.shape = initShape(fish.x, fish.y);
    return fish;
}

/*Update method*/

int main() {
    RenderWindow window(VideoMode({600, 600}), "Aquarium");
    Fish fish;
    BezierCurve bezier;
    if (!started) {
        fish = initFish(300.0f, 300.0f);
        started = true;
        bezier.generateBezierCurve(fish.x, fish.y, 600, 600);
    }

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            }
        }
        window.clear(Color::Blue);
        fish.moveAlongBezierCurve(&bezier, 600, 600);
        window.draw(fish.shape);
        window.display();
    }
}