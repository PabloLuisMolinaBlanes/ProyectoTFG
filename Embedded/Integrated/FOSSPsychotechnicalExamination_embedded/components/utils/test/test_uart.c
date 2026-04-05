#include "unity.h"
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
    TEST_ASSERT_EQUAL(0, read_from_uart());
}

TEST_CASE("The user shouldnt be able to make a read from an UART device without configuring it first", "[uart]") {
    TEST_ASSERT_EQUAL(1, read_from_uart());
}