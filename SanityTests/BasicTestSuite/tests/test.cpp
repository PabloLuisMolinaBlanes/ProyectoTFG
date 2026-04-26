#include <gtest/gtest.h>
#include "class_with_main.hpp"

TEST(HelloTestII, BasicAssertions) {
    // Act
    int result = add_two_numbers(2,2);
    // Assert
    EXPECT_EQ(4, result);
}