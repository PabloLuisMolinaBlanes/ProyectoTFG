#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "esp_timer.h"
#include "freertos/timers.h"

static const gpio_num_t button_pin = GPIO_NUM_13;
static const uint32_t sleep_time = 100;
#define BUTTON_GPIO 13

/*
gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << GPIO_NUM_13), // Select GPIO 13
    .mode = GPIO_MODE_INPUT,               // Set as input
    .pull_up_en = GPIO_PULLUP_ENABLE,     // Enable internal pull-up
    .pull_down_en = GPIO_PULLDOWN_DISABLE, // Disable pull-down
    .intr_type = GPIO_INTR_DISABLE        // Disable interrupts
};
*/
void app_main(void)
{
    gpio_reset_pin(button_pin);
    gpio_set_direction(button_pin, GPIO_MODE_INPUT);
    while (1) {
        //printf("%d\n", gpio_get_level(button_pin));
        if (gpio_get_level(button_pin) == 0) {
            printf("7900\n");
        }
        vTaskDelay(sleep_time/portTICK_PERIOD_MS);
    }
}