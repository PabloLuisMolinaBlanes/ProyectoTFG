#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "serial.hpp"
#include <memory>
#include <string.h>
#include <fstream>


using sf::Color;
using sf::CircleShape;
using sf::Event;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Clock;

#define NUMBER_OF_WALLS 5
#define DEGREE_OF_SEPARATION 0.48
#define NUMBER_OF_POSITIONS 200
#define INITIAL_X_WALL 450
#define INITIAL_X_WALL_2 100
#define INITIAL_Y_WALL 250
#define SIZE_X_WALL 50.0f
#define SIZE_Y_WALL 120.0f
#define INITIAL_X_CAR 140.0f
#define INITIAL_X_CAR_2 500.0f
#define INITIAL_Y_CAR 50.0f
#define SCREEN_SIZE_X 600
#define SCREEN_SIZE_Y 600
#define CAR_SIZE_X 20.0f
#define CAR_SIZE_Y 20.0f
#define FIRST_VALUE_FIRST_POTENTIOMETER 128
#define FIRST_VALUE_SECOND_POTENTIOMETER 142
#define SECOND_VALUE_FIRST_POTENTIOMETER 3139
#define SECOND_VALUE_SECOND_POTENTIOMETER 3155

bool started = false;
bool pressed = false;

std::int32_t real_time_elapsed = 0;
std::int32_t game_time_elapsed = 0;
int handle_turn = 0;

int test_data_1[NUMBER_OF_POSITIONS-NUMBER_OF_WALLS];
int test_data_2[NUMBER_OF_POSITIONS-NUMBER_OF_WALLS];

int position_counter_1 = 0;
int position_counter_2 = 0;

std::ofstream outfile_1;
std::ofstream outfile_2;

struct Point {
    float x;
    float y;
};

class Path {
    public:
        struct Point P0;
        struct Point P1;
        void generatePath(float car_x, float car_y, float screen_y) {
            P0.x = car_x;
            P0.y = car_y;
            P1.x = car_x;
            P1.y = screen_y;
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
        void moveAlongPath(struct Path *path) {
            float vel = path->P1.y - path->P0.y;
            float next_y = path->P0.y + vel*t;
            float next_dy = next_y-actual_y;
            t = t + 0.005;
            move(next_dy);
        }

        void move(float x_received) {
            actual_x = x_received;
            if (actual_x > SCREEN_SIZE_X) {
                x = SCREEN_SIZE_X-20;
            } else if (actual_x < 0) {
                x = 20;
            } else {
                x = actual_x;
            }
            shape.setPosition(sf::Vector2f(x, INITIAL_Y_CAR));
        }
};

sf::RectangleShape initShape(int pos_x, int pos_y) {
    sf::RectangleShape shape(sf::Vector2f(CAR_SIZE_X, CAR_SIZE_Y));
    shape.setPosition(sf::Vector2f(pos_x,pos_y));
    shape.setFillColor(sf::Color::Red);
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

void setPositions(sf::RectangleShape * walls, int * positions, int counter, int direction) {
    for (int i = 0; i < NUMBER_OF_WALLS; i++) {
        int nextPosition = walls[i].getPosition().x+(positions[counter]*direction);
        if (nextPosition < 0 || (abs(nextPosition-(SCREEN_SIZE_X/2)) < 50) || nextPosition > (SCREEN_SIZE_X - SIZE_X_WALL)) {
            nextPosition = walls[i].getPosition().x;
        } 
        walls[i].setPosition(sf::Vector2f(nextPosition, walls[i].getPosition().y));
        counter++;
    } 
} 

void initializeWalls(sf::RectangleShape * walls, int initial_x_wall, float size_x, float size_y) {
    for (int i = 0; i < NUMBER_OF_WALLS; i++) {
        walls[i] = initShape(initial_x_wall,INITIAL_Y_WALL*DEGREE_OF_SEPARATION*i,size_x,size_y);
    }
}

void drawWalls(RenderWindow * window, sf::RectangleShape * walls) {
    for (int i = 0; i < NUMBER_OF_WALLS; i++) {
        window->draw(walls[i]);
    }
}

void initializePositions(int * positions) {
    for (int i = 0; i < NUMBER_OF_WALLS; i++) {
        positions[i] = 0;
    }
    std::srand(1);
    int multiplier = 1;
    for (int i = NUMBER_OF_WALLS; i < NUMBER_OF_POSITIONS; i++) {
        int result = std::rand();
        if (result % 3 == 0) {
            multiplier = 1;
        } else if (result % 3 == 1) {
            multiplier = -1;
        } else {
            multiplier = 0;
        }
        int nextPosition = (10*multiplier);
        positions[i] = nextPosition; 
    }
}

int verifyCollision(Car car, sf::RectangleShape wall) {
    int result = car.shape.getPosition().x;
    int result_2 = wall.getPosition().x;
    if (result < result_2 || result > result_2+(SIZE_X_WALL-CAR_SIZE_X)) {
        return 0;
    }
    return 1;
}

int resolvePosition(int index, int * collection, int size_array) {
    if (index < 0) {
        return 0;
    } else if (index > size_array-1) {
        return collection[size_array-1]; 
    }   else {
        return collection[index]; 
    } 
}

void initializeLookUpTable(int * collection, int multiple) {
    int current_position = 0;
    for (int i = 0; i <= (multiple*SCREEN_SIZE_X)-multiple; i += multiple) {
        for (int j = i; j < (i+multiple); j++) {
            collection[j] = current_position;
        }
        current_position++;
    }
}

void add_data(int data, int potentiometer) {
    if (potentiometer == 1 && position_counter_1 < NUMBER_OF_POSITIONS-NUMBER_OF_WALLS) {
        test_data_1[position_counter_1] = data;
        position_counter_1++;
    }
    if (potentiometer == 2 && position_counter_2 < NUMBER_OF_POSITIONS-NUMBER_OF_WALLS) {
        test_data_2[position_counter_2] = data;
        position_counter_2++;
    }
}

int save_data() {
    std::string addResults_1 = "";
    std::string addResults_2 = "";
    for (int i = 0; i < NUMBER_OF_POSITIONS-NUMBER_OF_WALLS; i++) {
        addResults_1 += std::to_string(test_data_1[i]);
        if (i != NUMBER_OF_POSITIONS-NUMBER_OF_WALLS-1) {
            addResults_1 += ",";
        }
    }
    addResults_1 += "\n";
    for (int i = 0; i < NUMBER_OF_POSITIONS-NUMBER_OF_WALLS; i++) {
        addResults_2 += std::to_string(test_data_2[i]);
        if (i != NUMBER_OF_POSITIONS-NUMBER_OF_WALLS-1) {
            addResults_2 += ",";
        }
    }
    addResults_2 += "\n";
    outfile_1.open("second_test_1.txt", std::ios_base::app);
    outfile_2.open("second_test_2.txt", std::ios_base::app);
    outfile_1 << addResults_1;
    outfile_2 << addResults_2;
    return 0;
}

/*Update method*/

int main() {
    default_configure();
    serial_send(2);
    RenderWindow window(VideoMode({SCREEN_SIZE_X, SCREEN_SIZE_Y}), "Test1");
    Car car;
    Car car_2;
    sf::RectangleShape walls[NUMBER_OF_WALLS];
    sf::RectangleShape walls_2[NUMBER_OF_WALLS];
    int positions[NUMBER_OF_POSITIONS];
    Path path;
    sf::Clock clock;
    int positionCounter = 0;
    if (NUMBER_OF_POSITIONS < NUMBER_OF_WALLS) {
        printf("Error. Cannot have more positions than walls.\n");
        serial_send(3);
        exit(-1);
    }
    if (SECOND_VALUE_FIRST_POTENTIOMETER <= FIRST_VALUE_FIRST_POTENTIOMETER) {
        printf("Error. Top value of first potentiometer cannot be equal or shorter to bottom value");
        serial_send(3);
        exit(-1);
    }
    if (SECOND_VALUE_SECOND_POTENTIOMETER <= FIRST_VALUE_SECOND_POTENTIOMETER) {
        printf("Error. Top value of second potentiometer cannot be equal or shorter to bottom value");
        serial_send(3);
        exit(-1);
    }
    float division_1 = (SECOND_VALUE_FIRST_POTENTIOMETER-FIRST_VALUE_FIRST_POTENTIOMETER)/SCREEN_SIZE_X;
    if (division_1 < 1) {
        printf("Error, the range of the first potentiometer must be larger or equal to that of the screen size in the x coordinate");
        serial_send(3);
        exit(-1);
    } 
    float division_2 = (SECOND_VALUE_SECOND_POTENTIOMETER-FIRST_VALUE_SECOND_POTENTIOMETER)/SCREEN_SIZE_X;
    if (division_2 < 1) {
        printf("Error, the range of the second potentiometer must be larger or equal to that of the screen size in the x coordinate");
        serial_send(3);
        exit(-1);
    }
    const int multiple1 = (int)floor(division_1);
    const int multiple2 = (int)floor(division_2);
    const int lookuptable1_size = multiple1*SCREEN_SIZE_X;
    const int lookuptable2_size = multiple2*SCREEN_SIZE_X;
    int * lookuptable_firstPotentiometer = new int[lookuptable1_size];
    int * lookuptable_secondPotentiometer = new int[lookuptable2_size];
    initializeLookUpTable(lookuptable_firstPotentiometer, multiple1);
    initializeLookUpTable(lookuptable_secondPotentiometer, multiple2);
    if (!started) {
        car = initCar(INITIAL_X_CAR, INITIAL_Y_CAR);
        car_2 = initCar(INITIAL_X_CAR_2, INITIAL_Y_CAR);
        started = true;
        path.generatePath(car.x, car.y, 600);
        initializePositions(positions);
        initializeWalls(walls,INITIAL_X_WALL,SIZE_X_WALL, SIZE_Y_WALL);
        initializeWalls(walls_2,INITIAL_X_WALL_2,SIZE_X_WALL, SIZE_Y_WALL);
    }
    while (window.isOpen()) {
        while (clock.getElapsedTime().asMilliseconds() < 200) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<Event::Closed>()) {
                    serial_send(3);
                    window.close();
                }
            }
            const char * received = serial_read();
                if (strcmp(received, "") != 0) {
                    printf("Received raw serial data %s\n", received);
                    int position;
                    if (handle_turn == 0) {
                        position = resolvePosition(atoi(received)-FIRST_VALUE_FIRST_POTENTIOMETER, lookuptable_firstPotentiometer, lookuptable1_size);
                        car.move(position);
                    } else {
                        position = resolvePosition(SECOND_VALUE_SECOND_POTENTIOMETER-(atoi(received)-FIRST_VALUE_SECOND_POTENTIOMETER), lookuptable_secondPotentiometer, lookuptable2_size);
                        car_2.move(position);
                    } 
                    handle_turn = (handle_turn + 1) % 2;
                }
        }
        real_time_elapsed += clock.restart().asMilliseconds();
        add_data(car.x, 1);
        add_data(car_2.x, 2);
        window.clear(Color::Blue);
        drawWalls(&window, walls);
        drawWalls(&window, walls_2);
        window.draw(car.shape);
        window.draw(car_2.shape);
        window.display();
        if (positionCounter+NUMBER_OF_WALLS < NUMBER_OF_POSITIONS) {
            positionCounter++;
            setPositions(walls, positions, positionCounter, 1);
            setPositions(walls_2, positions, positionCounter, -1);
        } else {
            save_data();
            serial_send(3);
            exit(0);
        }
        game_time_elapsed += clock.getElapsedTime().asMilliseconds();
        real_time_elapsed += clock.getElapsedTime().asMilliseconds();
    }
}