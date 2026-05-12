#include <gtest/gtest.h>
#include "second_examination/definitions_second_examination.hpp"
#include "second_examination/second_examination.hpp"
#include <cmath>

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
    sf::RectangleShape walls[NUMBER_OF_WALLS];
    int initial_x_wall = INITIAL_X_WALL;
    float size_x = SIZE_X_WALL;
    float size_y = SIZE_Y_WALL; 
    // Arrange
    initializeWalls(walls, initial_x_wall, size_x, size_y);
    // Assert
    bool result = true;
    for (int i = 0; i<NUMBER_OF_WALLS; i++) {
        result = result & walls[i].getPosition().x == initial_x_wall;
        result = result & walls[i].getSize().x == size_x;
        result = result & walls[i].getSize().y == size_y;
    } 
    EXPECT_EQ(true, result);
}

TEST(InitializePositionsInitializesPositionsCorectly, BasicAssertions) {
    int positions[NUMBER_OF_POSITIONS];
    // Arrange
    initializePositions(positions);
    // Assert
    bool result = true;
    for (int i = 0; i<NUMBER_OF_POSITIONS; i++) {
        result = result && (positions[i] == -10 || positions[i] == 0 || positions[i] == 10);
    } 
    EXPECT_EQ(true, result);
}

TEST(InitializeLookUpTableInitializesTableCorectly, BasicAssertions) {
    float division_1 = (SECOND_VALUE_FIRST_POTENTIOMETER-FIRST_VALUE_FIRST_POTENTIOMETER)/SCREEN_SIZE_X;
    const int multiple = (int)floor(division_1);
    int collection[multiple*SCREEN_SIZE_X];
    // Arrange
    initializeLookUpTable(collection, multiple);
    // Assert
    bool result = true;
    int past_past_collection = -1;
    for (int i = 0; i<(multiple*SCREEN_SIZE_X)-multiple; i += multiple) {
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

TEST(PositionsAreAssignedCorrectly, BasicAssertions) {
    int positions[NUMBER_OF_POSITIONS];
    sf::RectangleShape walls[NUMBER_OF_WALLS];
    int initial_x_wall = 0;
    float size_x = SIZE_X_WALL;
    float size_y = SIZE_Y_WALL;
    // Arrange
    initializePositions(positions);
    initializeWalls(walls, initial_x_wall, size_x, size_y);
    bool result = true;
    for (int i = 0; i < NUMBER_OF_POSITIONS; i++) {
        for (int j = i; j < i+NUMBER_OF_WALLS; j++) {
            setPositions(walls, positions, j, 1);
        }
        for (int i = 0; i < NUMBER_OF_WALLS; i++) {
            result = result && (abs(walls[i].getPosition().x-300) >= 50) && (walls[i].getPosition().x <= 400);
        }
    }
    EXPECT_EQ(true, result);
}

TEST(VerifyCollisionVerifiesCorrectly, BasicAssertions) {
    // Arrange
    Car car = initCar(300, 300);
    // Arrange
    int pos_x = 300;
    int pos_y = 300;
    float size_x = 200.0f;
    float size_y = 200.0f;
    // Act
    sf::RectangleShape testShape = initShape(pos_x, pos_y, size_x, size_y);
    EXPECT_EQ(1, verifyCollision(car, testShape));
}

TEST(VerifyCollisionVerifiesCorrectly_II, BasicAssertions) {
    // Arrange
    Car car = initCar(299, 299);
    // Arrange
    int pos_x = 300;
    int pos_y = 300;
    float size_x = 200.0f;
    float size_y = 200.0f;
    // Act
    sf::RectangleShape testShape = initShape(pos_x, pos_y, size_x, size_y);
    EXPECT_EQ(0, verifyCollision(car, testShape));
}

TEST(VerifyCollisionVerifiesCorrectly_III, BasicAssertions) {
    // Arrange
    Car car = initCar(331, 331);
    // Arrange
    int pos_x = 300;
    int pos_y = 300;
    float size_x = 50.0f;
    float size_y = 50.0f;
    // Act
    sf::RectangleShape testShape = initShape(pos_x, pos_y, size_x, size_y);
    EXPECT_EQ(0, verifyCollision(car, testShape));
}

TEST(VerifyCollisionVerifiesCorrectly_IV, BasicAssertions) {
    // Arrange
    Car car = initCar(330, 330);
    // Arrange
    int pos_x = 300;
    int pos_y = 300;
    float size_x = 50.0f;
    float size_y = 50.0f;
    // Act
    sf::RectangleShape testShape = initShape(pos_x, pos_y, size_x, size_y);
    EXPECT_EQ(1, verifyCollision(car, testShape));
}

TEST(VerifyResolvePositionI, BasicAssertions) {
    // Arrange
    int test[2] = {0,1}; 
    EXPECT_EQ(0, resolvePosition(-1, test, 2));
}

TEST(VerifyResolvePositionII, BasicAssertions) {
    // Arrange
    int test[2] = {0,1}; 
    EXPECT_EQ(0, resolvePosition(0, test, 2));
}

TEST(VerifyResolvePositionIII, BasicAssertions) {
    // Arrange
    int test[2] = {0,1}; 
    EXPECT_EQ(1, resolvePosition(1, test, 2));
}

TEST(VerifyResolvePositionIV, BasicAssertions) {
    // Arrange
    int test[2] = {0,1}; 
    EXPECT_EQ(1, resolvePosition(2, test, 2));
}

TEST(VerifyResolvePositionV, BasicAssertions) {
    // Arrange
    int test[2] = {0,1}; 
    EXPECT_EQ(1, resolvePosition(3, test, 2));
}