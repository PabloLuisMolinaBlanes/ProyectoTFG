# FOSSPsychotechnicalExamination - Parte embedded

## Introducción

Este programa implementa los programas del proyecto FOSSPsychotechnicalExamination que se ejecutan en el microcontrolador.

Para leer más sobre FOSSPsychotechnicalExamination, consúltese el documento README.md en el fichero raiz del proyecto.

## FAQ

### ¿Con qué placas se ha probado esto?

El desarrollador ha probado la aplicación con una placa **ESP32-DevKitC V4**.

Para compilar con ESP-IDF, se puede asumir una placa **ESP32-Chip (via ESP-PROG)** si se dispone ya de la placa anterior.

### ¿Con qué versión de ESP-IDF se ha desarrollado el proyecto?

Se ha desarrollado en la versión v5.5.3 de ESP-IDF.

### ¿Se ha utilizado inteligencia artificial generativa en este proyecto?

No he utilizado IA generativa de forma deliberada para realizar ninguna parte de este proyecto; esto incluye documentación, código fuente, y parámetros de configuración o construcción.

Aún así, utilizo librerías externas, hay algunas porciones de código fuente que han sido tomadas de Internet, y he consultado documentación externa; desconozco su provenencia, y por ende, no puedo asegurar que no haya habido IA generativa involucrada en su creación.


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

Este componente incluye toda la funcionalidad relativa al primer examen psicotécnico.

Para utilizarlo, primero se ha de configurar los pines GPIO a través de la función ```configure_first_test```, tras ello, se ha de llamar al método ```first_examination_loop```.

#### ```second_examination.c```

Este componente incluye toda la funcionalidad relativa al segundo examen psicotécnico.

### ```utils```

```utils``` es un componente del proyecto que implementa funcionamiento que asiste a los exámenes psicotécnicos en su funcionamiento

#### ```uart.c```

```uart.c``` es un componente auxiliar del proyecto. Tiene la responsabilidad de proporcionar métodos para: 

- Configurar un dispositivo UART (por defecto, asumimos un dispositivo USB-to-UART en el puerto UART de consola por defecto)
- Leer datos transferidos por el puerto UART.

### ```main.c```

```main.c``` es el componente principal del proyecto. Su funcionamiento principal consiste en un loop que dispone del siguiente funcionamiento:

- Primero, inicializa un dispositivo UART con valores por defecto.
- Después, se dedica a leer de este dispositivo UART buscando un string específico "test_1" o "test_2", donde cada string se asocia a un examen psicotécnico concreto; si lee alguno de estos strings, llama al loop que implementa el examen correspondiente, y este toma el control del programa.


