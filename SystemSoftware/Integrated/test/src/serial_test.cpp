#include <gtest/gtest.h>
#include "serial.hpp"

TEST(HelloTestII, BasicAssertions) {
    // Act
    int result = serial_send(1);
    // Assert
    EXPECT_EQ(1, result);
}

/*TEST(SanityTest, BasicAssertions) {
    EXPECT_EQ(test, test);
}*/

TEST(HelloTest, BasicAssertions) {
    // Arrange
    // Act
    default_configure();
    serial_send(1);
    char * result = serial_read();
    printf("Received: %s\n", result);
    // Assert
    EXPECT_EQ((unsigned char *)"test_1", (unsigned char *) result);
}