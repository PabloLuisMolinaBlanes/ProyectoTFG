#include <stdio.h>
#include "first_examination.h"
#include "second_examination.h"
#include "uart.h"

#define MILLISECONDS 20
#define TEST_1 1
#define TEST_2 2

void app_main(void)
{
    configure_uart_with_default_options();
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