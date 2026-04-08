
const unsigned char msg[] = { 't', 'e', 's', 't', '_', '1' };
const unsigned char message_2[] = { 't', 'e', 's', 't', '_', '2' };
const unsigned char message_3[] = { 'e', 'x', 'i', 't' };

/*
Esta función realiza las funciones de configuración del dispositivo serial.

Por defecto, la configuración dispone de los siguientes atributos:

- No hay bit de paridad
- 8 bits por byte
- Por defecto, se ha de leer \n para leer línea

 */
int default_configure();

/*
Esta función lee a partir del dispositivo serial por defecto.
*/
char * serial_read();


/*
Esta función escribe a través del dispositivo serial elegido por defecto.
*/
int serial_send(const unsigned char * data);