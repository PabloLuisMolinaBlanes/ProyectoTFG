#include <gtest/gtest.h>
#include "second_examination/second_examination.hpp"

TEST(InitShapeInitsShapeWithCorrectPosXAndPosY, BasicAssertions) {
    // Arrange
    int pos_x = 35;
    int pos_y = 35;
    // Act
    sf::RectangleShape testShape = initShape(pos_x, pos_y);
    // Assert
    bool result = testShape.getPosition().x == 35 && testShape.getPosition().y == 35;
    EXPECT_EQ(true, result);
}

TEST(InitShapeInitsShapeWithCorrectPosXAndPosYAndSize, BasicAssertions) {
    // Arrange
    int pos_x = 35;
    int pos_y = 35;
    float size_x = 45.0f;
    float size_y = 45.0f;
    // Act
    sf::RectangleShape testShape = initShape(pos_x, pos_y, size_x, size_y);
    // Assert
    bool result = testShape.getPosition().x == 35 && testShape.getPosition().y == 35;
    bool result_2 = testShape.getSize().x == 45.0f && testShape.getSize().y == 45.0f;
    bool finalResult = result && result_2;
    EXPECT_EQ(true, finalResult);
}

TEST(InitCarActuallyInitsTheCar, BasicAssertions) {
    // Arrange
    Car car = initCar(200, 200);
    // Assert
    bool result = car.x == 200;
    bool result_2 = car.y == 200;
    bool result_3 = car.actual_x == 200;
    bool result_4 = car.actual_y == 200;
    EXPECT_EQ(true, result && result_2 && result_3 && result_4);
}

TEST(InitializeWallsInitializesWallsCorectly, BasicAssertions) {
    sf::RectangleShape walls[5];
    int initial_x_wall = 0;
    float size_x = 200;
    float size_y = 200; 
    // Arrange
    initializeWalls(walls, initial_x_wall, size_x, size_y);
    // Assert
    bool result = true;
    for (int i = 0; i<5; i++) {
        result = result & walls[i].getPosition().x == initial_x_wall;
        result = result & walls[i].getSize().x == size_x;
        result = result & walls[i].getSize().y == size_y;
    } 
    EXPECT_EQ(true, result);
}

TEST(InitializePositionsInitializesPositionsCorectly, BasicAssertions) {
    int positions[200];
    // Arrange
    initializePositions(positions);
    // Assert
    bool result = true;
    for (int i = 0; i<200; i++) {
        result = result && (positions[i] == -10 || positions[i] == 0 || positions[i] == 10);
    } 
    EXPECT_EQ(true, result);
}

TEST(InitializeLookUpTableInitializesTableCorectly, BasicAssertions) {
    int collection[3000];
    int multiple = 5;
    // Arrange
    initializeLookUpTable(collection, multiple);
    // Assert
    bool result = true;
    int past_past_collection = -1;
    for (int i = 0; i<3000; i += multiple) {
        int past_collection = collection[i];
        result = result && collection[i] != past_past_collection;  
        for (int j = i; j < i+multiple; j++) {
            result = result && collection[j] == past_collection;
            past_collection = collection[j];  
        }
        past_past_collection = collection[i]; 
    }
    EXPECT_EQ(true, result);
}