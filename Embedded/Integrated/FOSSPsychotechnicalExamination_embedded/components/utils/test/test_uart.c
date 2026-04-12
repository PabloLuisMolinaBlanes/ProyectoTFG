#include "unity.h"
#include "stdio.h"
#include "stdlib.h"
#include "uart.h"

TEST_CASE("UART default configuration method correctly returns 0", "[uart]")
{
    TEST_ASSERT_EQUAL(0, configure_uart_with_default_options());
}

TEST_CASE("The user shouldnt be able to configure the UART device twice", "[uart]") {
    configure_uart_with_default_options();
    TEST_ASSERT_EQUAL(1, configure_uart_with_default_options());
}

TEST_CASE("Read from UART should return '0' straight away as no bits are received", "[uart]") {
    configure_uart_with_default_options();
    TEST_ASSERT_EQUAL(0, read_from_uart(200));
}

TEST_CASE("The user shouldnt be able to make a read from an UART device without configuring it first", "[uart]") {
    TEST_ASSERT_EQUAL(1, read_from_uart(200));
}

TEST_CASE("When the UART device reads something from the cable, it should return 0", "[uart]") {
    printf("You have 2 seconds to write down something.\n");
    configure_uart_with_default_options();
    TEST_ASSERT_EQUAL(0, read_from_uart(2000));
}

TEST_CASE("When the UART device reads test_1 from the cable, it should return 1", "[uart]") {
    printf("You have 4 seconds to write down.\n");
    configure_uart_with_default_options();
    TEST_ASSERT_EQUAL(1, read_from_uart(4000));
}