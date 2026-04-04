#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
 
static const int RX_BUF_SIZE = 128;

void app_main(void)
{   
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    ESP_ERROR_CHECK(uart_driver_install(CONFIG_ESP_CONSOLE_UART_NUM, 256, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(CONFIG_ESP_CONSOLE_UART_NUM, &uart_config));
    char chr[RX_BUF_SIZE];
    while(1){
        const int rxBytes = uart_read_bytes(CONFIG_ESP_CONSOLE_UART_NUM, chr, RX_BUF_SIZE, 200);
        if (rxBytes > 0) {
            printf("Read %d bytes: '%s'\n", rxBytes, chr);
        }
        vTaskDelay(200);
    }
}
