# FOSSPsychotechnicalExamination - Parte embedded

## Introducción

## FAQ

### ¿Con qué placas se ha probado esto?

El desarrollador ha probado la aplicación con una placa **ESP32-DevKitC V4**.

Para compilar con ESP-IDF, se puede asumir una placa **ESP32-Chip (via ESP-PROG)** si se dispone ya de la placa anterior.

### ¿Con qué versión de ESP-IDF se ha desarrollado el proyecto?

Se ha desarrollado en la versión v5.5.3 de ESP-IDF.

## Instrucciones de compilación

### Para proyecto 'main'

1. [Instale ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html#installation)
2. Inicialize ESP-IDF con el comando ```source "$HOME/.espressif/tools/activate_idf_<version>.sh"```
3. Acceda al directorio raiz (donde se encuentra este README)
4. Realize la configuración que desee con ```idf.py menuconfig```
5. Ejecute el comando ```idf.py -p <port> build```

### Para proyecto 'test'

1. [Instale ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/index.html#installation)
2. Inicialize ESP-IDF con el comando ```source "$HOME/.espressif/tools/activate_idf_<version>.sh"```
3. Acceda al directorio ```test```
4. Realize la configuración que desee con ```idf.py menuconfig```
5. Ejecute el comando ```idf.py -p <port> build```

## Descripción de los componentes del proyecto

### ```examinations```

```examinations``` es un componente del proyecto que implementa todo el funcionamiento del microcontrolador relativo a los exámenes psicotécnicos.

#### ```first_examination.c```

#### ```second_examination.c```

### ```utils```

```utils``` es un componente del proyecto que implementa funcionamiento que asiste a los exámenes psicotécnicos en su funcionamiento

#### ```uart.c```

### ```main.c```

```main.c``` es el componente principal del proyecto. Su funcionamiento principal consiste en un loop que dispone del siguiente funcionamiento:

- Primero, inicializa un dispositivo UART con valores por defecto.
- Después, se dedica a leer de este dispositivo UART buscando un string específico "test_1" o "test_2", donde cada string se asocia a un examen psicotécnico concreto; si lee alguno de estos strings, llama al loop que implementa el examen correspondiente, y este toma el control del programa.


