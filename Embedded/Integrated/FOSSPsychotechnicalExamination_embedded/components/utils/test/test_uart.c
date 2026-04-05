#include "unity.h"
#include "uart.h"

TEST_CASE("UART default configuration method correctly returns 0", "[uart]")
{
    TEST_ASSERT_EQUAL(0, configure_uart_with_default_options());
}