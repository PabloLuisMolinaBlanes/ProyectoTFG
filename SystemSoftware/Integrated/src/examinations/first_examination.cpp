/*Includes*/
#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <inttypes.h>
#include "serial.hpp"
#include <fstream>

/*Importaciones*/
using sf::Color;
using sf::CircleShape;
using sf::Event;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Clock;

/*Parámetros y variables*/
bool started = false;

std::int32_t real_time_elapsed = 0;
std::int32_t game_time_elapsed = 0;

#define NUMBER_OF_TESTS 3

float test_data[NUMBER_OF_TESTS];

int test_counter = 0;

std::ofstream outfile;

struct Point {
    float x;
    float y;
};

/*Clases*/

class Path {
    public:
        // Punto inicial del camino
        struct Point P0;
        // Punto final del camino
        struct Point P1;
        //Genera un camino a seguir para el coche
        void generatePath(float car_x, float car_y, float screen_x) {
            P0.x = car_x;
            P0.y = car_y;
            P1.x = screen_x;
            P1.y = car_y;
        }
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
        float t = 0;
        // Intervalos de tiempo (1 por ejecución)
        float velocity = 0.005;
        sf::RectangleShape shape;
        //Calcula el valor de la ecuación X_F = X_0+V*t, y utiliza este valor para calcular el desplazamiento en X que se ha de hacer desde la posición actual del coche
        void moveAlongPath(struct Path *path, float screen_x) {
            float vel = path->P1.x - path->P0.y;
            float next_x = path->P0.x + vel*t;
            float next_dx = next_x-actual_x;
            t = t + velocity;
            move(screen_x, next_dx);
        }
        //Realiza el movimiento del coche en pantalla a partir del desplazamiento dx
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

/*Métodos auxiliares*/

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
// Iniciamos los parámetros del 'vehículo' en pantalla
Car initCar(int car_x, int car_y) {
    Car car;
    car.x = car_x;
    car.y = car_y;
    car.actual_x = car.x;
    car.actual_y = car.y;
    car.shape = initShape(car.x, car.y);
    return car;
}
// Reiniciamos los parámetros de la examinación
void reset_test(Car * car) {
    car->shape.setPosition(sf::Vector2f(300.0f, 300.0f));
    car->velocity = 0.005;
    car->t = 0;
    car->x = 300.0f;
    car->actual_x = car->x;
}

void add_data(float data) {
    test_data[test_counter] = data;
}
/*Guardamos los datos recolectados durante la examinación*/
int save_data() {
    std::string addResults = "";
    // Formateado de los resultados ("<tiempo_1>,<tiempo_2>,...")
    for (int i = 0; i < NUMBER_OF_TESTS; i++) {
        addResults += std::to_string(test_data[i]);
        if (i != NUMBER_OF_TESTS-1) {
            addResults += ",";
        }
    }
    // Nos aseguramos que el buffer hace flush
    addResults += "\n";
    outfile.open("first_test.txt", std::ios_base::app);
    outfile << addResults;
    return 0;
}

/*Función principal*/

int main() {
    /*Configuramos el puerto serial y le indicamos al microcontrolador que puede comenzar a ejecutar su programa de examinacion*/
    default_configure();
    serial_send(1);
    /*Aquí se inicializan variables locales para la examinacion*/ 
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
    /*Cuando lo hemos inicializado todo, entramos en este bucle*/
    while (window.isOpen()) {
        /*Buscamos asegurar que se ejecuta lógica del examen solo cada 16 milisegundos*/
        while (clock.getElapsedTime().asMilliseconds() < 16) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<Event::Closed>()) {
                    // Indica al microcontrolador que vamos a terminar la examinación.
                    serial_send(3);
                    window.close();
                }
            }
        }
        real_time_elapsed += clock.restart().asMilliseconds();
        /*Lee del serial, y actua solo si hemos recibido datos*/
        const char * received = serial_read();
        if (strcmp(received, "") != 0){
            // Agrega el momento en el tiempo en el que pulsamos el botón
            add_data(car.t);
            // Reinicia la examinación
            reset_test(&car);
            test_counter++;
            /*Si hemos realizado el número de tests necesarios, guardamos datos y cerramos*/
            if (test_counter >= NUMBER_OF_TESTS) {
                save_data();
                // Indica al microcontrolador que vamos a terminar la examinación.
                serial_send(3);
                exit(0);
            }
        }
        /*Llamadas a métodos relativos a la interfaz gráfica*/
        window.clear(Color::Blue);
        car.moveAlongPath(&path, 600);
        window.draw(car.shape);
        window.draw(wall);
        window.display();
        game_time_elapsed += clock.getElapsedTime().asMilliseconds();
        real_time_elapsed += clock.getElapsedTime().asMilliseconds();
    }
}