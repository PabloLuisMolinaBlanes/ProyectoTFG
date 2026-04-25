/*Includes de la aplicación*/

#include "uart.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

// Indicamos el pin número 13 de la placa como nuestro pin de entrada
static const gpio_num_t button_pin = GPIO_NUM_13;
#define BUTTON_GPIO 13

// Indica al programa cada cuánto ha de comprobar el voltaje del botón
#define MILLISECONDS_TO_CHECK 100

// Este parámetro indica si se ha configurado o no los pines GPIO - 0 es que no, y 1 es que sí
int configured_first = 0;

void configure_first_test() {
    /*Si ya hemos configurado, no hace falta volver a configurar otra vez*/
    if (configured_first == 1) {
        return;
    }
    // Configura el pin button_pin como pin de entrada.
    gpio_reset_pin(button_pin);
    gpio_set_direction(button_pin, GPIO_MODE_INPUT);

    // Configura dispositivo UART de no haber sido configurado antes
    if (is_uart_already_configured() == 0) {
        configure_uart_with_default_options();
    }
    configured_first = 1;
}

void first_examination_loop() {
    /*No se debe iniciar el programa sin configurar antes la examinación*/
    if (configured_first == 0) {
        printf("Error. You should configure this examination first configure_first_test()\n");
        return;
    }
    while (1) {
        /*Comprueba si el boton está siendo pulsado en el momento de la llamada */
        if (gpio_get_level(button_pin) == 0) {
            printf("7900\n");
        }

        /*Comprueba si host ha enviado un valor para salir */
        if (read_from_uart(MILLISECONDS_TO_CHECK) == EXIT_VALUE) {
            break;
        }
        // Duerme el tiempo indicado
        vTaskDelay(MILLISECONDS_TO_CHECK/portTICK_PERIOD_MS);
    }
}