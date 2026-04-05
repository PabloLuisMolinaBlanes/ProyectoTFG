#include <stdio.h>
#include <string.h>
#include "driver/uart.h"
 
#define RX_BUF_SIZE 128
char chr[RX_BUF_SIZE];

void task_1() {
    while (1) {
        memset(&chr, '\0', sizeof(chr));
        int rxBytes = uart_read_bytes(CONFIG_ESP_CONSOLE_UART_NUM, chr, RX_BUF_SIZE, 200/portTICK_PERIOD_MS);
        if (rxBytes > 0) {
            if (strcmp(chr, "exit") == 0) {
                printf("Success from task 1\n");
                break;
            } else {
                printf("Fail\n");
                printf("%s\n", chr);
            }
        }
        vTaskDelay(200);
    } 
}

void task_2() {
    while (1) {
        memset(&chr, '\0', sizeof(chr));
        int rxBytes = uart_read_bytes(CONFIG_ESP_CONSOLE_UART_NUM, chr, RX_BUF_SIZE, 200/portTICK_PERIOD_MS);
        if (rxBytes > 0) {
            if (strcmp(chr, "exit") == 0) {
                printf("Success from task 2\n");
                break;
            } else {
                printf("Fail\n");
                printf("%s\n", chr);
            }
        }
        vTaskDelay(200);
    } 
}

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
    while(1){
        memset(&chr, '\0', sizeof(chr));
        int rxBytes = uart_read_bytes(CONFIG_ESP_CONSOLE_UART_NUM, chr, RX_BUF_SIZE, 200/portTICK_PERIOD_MS);
        if (rxBytes > 0) {
            if (strcmp(chr, "test_1") == 0) {
                printf("Success from app_main for test_1\n");
                task_1();
            } else if (strcmp(chr, "test_2") == 0) {
                printf("Success from app_main for test_2\n");
                task_2();
            } 
            //printf("%s", chr);
            //printf("%.*s\n", rxBytes, chr);
            //char* test_str = "This is a test string.\n";
            //uart_write_bytes(CONFIG_ESP_CONSOLE_UART_NUM, chr, 6);
        }
        vTaskDelay(200);
    }
}
