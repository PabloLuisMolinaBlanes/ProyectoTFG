
/*
Esta función realiza las funciones de configuración del dispositivo serial.

Por defecto, la configuración dispone de los siguientes atributos:

- No hay bit de paridad
- 8 bits por byte
- Por defecto, se ha de leer \n para leer línea

 */
int default_configure();

/*
Esta función lee a partir del dispositivo serial elegido.
*/
char * serial_read();


/*
Esta función escribe a través del dispositivo serial.
*/
int serial_send(char * data);