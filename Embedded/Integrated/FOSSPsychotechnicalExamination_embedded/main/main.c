/*Includes*/

#include <stdio.h>
#include "first_examination.h"
#include "second_examination.h"
#include "uart.h"

/*Definiciones*/
#define MILLISECONDS 20
#define TEST_1 1
#define TEST_2 2

/*Método principal*/
void app_main(void)
{
    // Configura el dispositivo UART
    configure_uart_with_default_options();
    /*Bucle principal. Lee del dispositivo UART cada 200 milisegundos, y actua conforme a lo recibido.*/
    while (1) {
        int result = read_from_uart(200);
        switch(result){
            case TEST_1:
                configure_first_test();
                first_examination_loop();
                break;
            case TEST_2:
                configure_second_test();
                second_examination_loop();
                break;
        } 
    } 
}