#include <SFML/Graphics.hpp>

struct Point {
    float x;
    float y;
};

class Path {
    public:
        // Punto inicial del camino
        struct Point P0;
        // Punto final del camino
        struct Point P1;
        //Genera un camino a seguir para el coche
        void generatePath(float car_x, float car_y, float screen_x);
};

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
        // Tiempo pasado (se mide en intervalos de velocity, no utilizamos segundos reales)
        float t;
        // Intervalos de tiempo (1 por ejecución)
        float velocity;
        sf::RectangleShape shape;
        //Calcula el valor de la ecuación X_F = X_0+V*t, y utiliza este valor para calcular el desplazamiento en X que se ha de hacer desde la posición actual del coche
        void moveAlongPath(struct Path *path, float screen_x);
        //Realiza el movimiento del coche en pantalla a partir del desplazamiento dx
        void move(float screen_x, float dx);
};

sf::RectangleShape initShape(int pos_x, int pos_y);

sf::RectangleShape initShape(int pos_x, int pos_y, float size_x, float size_y);

Car initCar(int car_x, int car_y);

void reset_test(Car * car);

void add_data(float data);

int save_data();
