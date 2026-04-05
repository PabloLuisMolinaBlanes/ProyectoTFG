#include "driver/uart.h"
#include "uart.h"

int configured = 0;

const uart_config_t default_uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
};

char uart_buffer[RX_BUF_SIZE];

int configure_uart_with_default_options() {
    if (configured == 1) {
        printf("Error. configure_uart_with_default_options() has been run previously already\n");
        return 1;
    }
    ESP_ERROR_CHECK(uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM, 256, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(CONFIG_ESP_CONSOLE_UART_NUM, &default_uart_config));
    configured = 1;
    return 0;
}

int read_from_uart(int nMilliseconds) {
    if (configured == 0) {
        printf("Error. You should configure the UART device first by running configure_uart_with_default_options()\n");
        return 1;
    }
    memset(&uart_buffer, '\0', sizeof(uart_buffer));
    int rxBytes = uart_read_bytes(CONFIG_ESP_CONSOLE_UART_NUM, uart_buffer, RX_BUF_SIZE, nMilliseconds/portTICK_PERIOD_MS);
    if (rxBytes > 0) {
        return 1;
    } 
    return 0;
}

int is_uart_already_configured() {
    return configured;
} 