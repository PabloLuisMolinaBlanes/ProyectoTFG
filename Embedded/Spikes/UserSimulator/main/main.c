#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

//static const gpio_num_t led_pin = GPIO_NUM_13;
static const uint32_t sleep_time = 1000;
//#define BLINK_GPIO 13


void app_main(void)
{
    //uint8_t led_state = 0;

    //gpio_reset_pin(led_pin);
    //gpio_set_direction(led_pin, GPIO_MODE_OUTPUT);

    while (1) {
        printf("%d\n",7900);
        //led_state = !led_state;
        //gpio_set_level(led_pin, led_state);

        vTaskDelay(sleep_time/portTICK_PERIOD_MS);
    }
}