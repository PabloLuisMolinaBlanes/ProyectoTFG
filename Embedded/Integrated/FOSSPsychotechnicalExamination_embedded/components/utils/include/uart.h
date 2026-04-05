#include <stdio.h>
#include <string.h>

#ifndef RX_BUF_SIZE
#define RX_BUF_SIZE 128
#endif

#define EXIT_VALUE 3


/*
Esta funcion configura el dispositivo UART con opciones por defecto.

Se asume la siguiente configuración por defecto:
- 115200 de baudio serial
- 8 bits por byte
- Sin paridad
- 1 stop byte
- Sin flow control
- Reloj por defecto

Se asume que se utilizará el UART número 0, tradicionalmente asignado
al puerto UART-to-USB. No se asignan pins RX ni TX por defecto, ya que
se asume una conexión UART-to-USB con la placa, y no un dispositivo
UART externo.
*/
int configure_uart_with_default_options();


/*
Esta función lee del puerto UART, y devuelve un entero indicando si ha realizado un cambio de tarea.

Por defecto devuelve 0, indicando que no ha realizado un cambio de tarea.
Si ha realizado un cambio de tarea, devuelve un número que indica la tarea a la que ha cambiado.

Esta función no es activada por interrupción; se debe llamar manualmente por el desarrollador.
*/
int read_from_uart(int nMilliseconds);