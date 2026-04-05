#include "uart.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

static const gpio_num_t button_pin = GPIO_NUM_13;
static const uint32_t sleep_time = 500;
#define BUTTON_GPIO 13
#define MILLISECONDS_TO_CHECK 10


int configured = 0;

void configure_first_test() {
    if (configured == 1) {
        return;
    }
    gpio_reset_pin(button_pin);
    gpio_set_direction(button_pin, GPIO_MODE_INPUT);
    if (is_uart_already_configured() == 0) {
        configure_uart_with_default_options();
    }
    configured = 1;
}

void first_examination_loop() {
    while (1) {
        if (gpio_get_level(button_pin) == 0) {
            printf("7900\n");
        }
        if (read_from_uart(MILLISECONDS_TO_CHECK) == EXIT_VALUE) {
            break;
        }
        vTaskDelay(sleep_time/portTICK_PERIOD_MS);
    }
}