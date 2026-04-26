#include <SFML/Graphics.hpp>

struct Point;

class Path;

class Car;

sf::RectangleShape initShape(int pos_x, int pos_y);

sf::RectangleShape initShape(int pos_x, int pos_y, float size_x, float size_y);

Car initCar(int car_x, int car_y);
