#include <gtest/gtest.h>
#include "first_examination/first_examination.hpp"

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

TEST(ResetTestActuallyAffectsTheCar, BasicAssertions) {
    // Arrange
    Car car = initCar(200, 200);
    float car_y_old = car.y;
    float car_actual_y_old = car.actual_y;
    // Act
    reset_test(&car);
    // Assert
    bool result = car.t == 0;
    bool result_2 = car.x == 300.0f;
    bool result_3 = car.actual_x == 300.0f;
    bool result_4 = car.y == car_y_old;
    bool result_5 = car.actual_y == car_actual_y_old;
    EXPECT_EQ(true, result && result_2 && result_3 && result_4 && result_5);
}