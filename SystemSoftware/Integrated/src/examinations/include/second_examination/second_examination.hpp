#include <SFML/Graphics.hpp>

class Car {
    public:
        // Verdadera posición x del coche.
        float actual_x;
        // Verdadera posición y del coche
        float actual_y;
        // Posición en x mostrada, no puede superar los bordes en x de la pantalla
        float x;
        // Posición en y mostrada, no puede superar los bordes en y de la pantalla
        float y;
        sf::RectangleShape shape;
        //Realiza el movimiento del coche en pantalla a partir del desplazamiento dx
        void move(float x_received);
};

sf::RectangleShape initShape(int pos_x, int pos_y);

sf::RectangleShape initShape(int pos_x, int pos_y, float size_x, float size_y);

Car initCar(int car_x, int car_y);

void initializeWalls(sf::RectangleShape * walls, int initial_x_wall, float size_x, float size_y);

void setPositions(sf::RectangleShape * walls, int * positions, int counter, int direction);

void initializePositions(int * positions);

int verifyCollision(Car car, sf::RectangleShape wall);

int resolvePosition(int index, int * collection, int size_array);

void initializeLookUpTable(int * collection, int multiple);