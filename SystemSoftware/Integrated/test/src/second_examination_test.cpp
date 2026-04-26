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