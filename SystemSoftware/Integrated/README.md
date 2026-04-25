# FOSSPsychotechnicalExamination - Parte System Software

## Introducción

Este programa implementa los programas del proyecto FOSSPsychotechnicalExamination que se ejecutan en el SBC (Single Board Computer).

Para leer más sobre FOSSPsychotechnicalExamination, consúltese el documento README.md en el fichero raiz del proyecto.

## FAQ

### ¿Cuáles son los requisitos para ejecutar este programa?

Lo más posible es que vayas a necesitar un dispositivo con una distribución Linux instalada para ejecutar los programas; debido a que en muchas partes del programa se asume un sistema operativo Linux por defecto; por ejemplo, en ```serial.cpp``` se hace una referencia explícita a un archivo de sistema estándar en sistemas Linux.

Para ejecutar la parte de interfaz gráfica; tendrás que tener por lo menos 1GB de memoria RAM y un motor de escritorio probablemente.

Las examinaciones son imposibles de realizar sin un dispositivo empotrado externo que pueda ejecutar el siguiente programa, complementario a este programa: https://github.com/PabloLuisMolinaBlanes/ProyectoTFG/tree/main/Embedded/Integrated/FOSSPsychotechnicalExamination_embedded

### ¿En dónde se ha probado este proyecto?

Se ha probado originalmente en un dispositivo Raspberry Pi 5 16GB, con sistema operativo Raspberry Pi OS.

No se ha probado en Windows, en Mac OS, o en ninguna otra distribución GNU/Linux

### ¿Qué librerías externas se utilizan en este software?

- [SFML](https://www.sfml-dev.org/) - bajo licencia zlib/png
- [GTK](https://www.gtk.org/) - bajo licencia GNU LGPL (GNU Lesser General Public License)

### ¿Se ha utilizado IA Generativa en la creación de este proyecto?

No he utilizado IA generativa de forma deliberada para realizar ninguna parte de este proyecto; esto incluye documentación, código fuente, y parámetros de configuración o construcción.

Aún así, utilizo librerías externas, hay algunas porciones de código fuente que han sido tomadas de Internet, y he consultado documentación externa; desconozco su provenencia, y por ende, no puedo asegurar que no haya habido IA generativa involucrada en su creación.

## Instrucciones de compilación del proyecto

Para compilar el proyecto; se deben seguir las siguientes instrucciones:

1. Descargar e instalar [CMake](https://cmake.org/download/)
2. Acceder al directorio raíz del proyecto.
3. Ejecutar el comando ```cmake .```. Esto sirve para generar los archivos .make correctos
4. Ejecutar el comando ```cmake --build .```. Los binarios se guardarán en la carpeta bin/

## Descripción de los componentes del proyecto

### ```examinations```

Este es el componente principal del software; implementa toda la funcionalidad relativa a examinaciones.

El funcionamiento general de los programas pertenecientes a este componente consiste en:

- Inicializar una interfaz de usuario gráfica
- Configurar y ejecutar la lógica relativa a las examinaciones
- Escuchar eventos enviados a través del cableado serial (por defecto se asume un dispositivo USB-to-UART es quien manda los datos) y actuar respecto a lo recibido
- Almacenar los resultados de las examinaciones.

#### ```first_examination.cpp```

Aquí se implementa todo lo relativo a la primera examinación, la prueba de tiempo de anticipación.

Más o menos, el funcionamiento consiste en lo siguiente:

- Primero se inicializan los parámetros, clases y valores relativos a la examinación.
- Después se entra en un bucle, donde se comprueba si se ha mandado información por el dispositivo serial, y si es así, reinicia la examinación o termina la examinación.
- Al finalizar la examinación, guarda toda la información recolectada sobre este para su auditoría, y cierra el programa de forma automática

#### ```second_examination.cpp```

Aquí se implementa todo lo relativo a la primera examinación, la prueba de coordinación mano-ojo.

Tiene un funcionamiento algo más complejo que la otra examinación.

- Primero se inicializan todos los parámetros, clases y valores; incluidos una serie de vallas, posiciones, y dos lookup tables; uno asociado con cada potenciómetro.
- Se calculan una serie de parámetros para inicializar de forma correcta los lookup tables
- Después, se entra en un bucle; donde se obtiene el voltaje recibido del potenciómetro respectivo, y se realizan los siguientes pasos: 
    - Se obtiene el lookup table que corresponde al potenciómetro del que proviene el voltaje
    - Se transforma este voltaje a un índice en el lookup table.
    - A partir de este índice calculado, obtenemos una posición de x
    - El vehículo asociado al potenciómetro donde viene el voltaje se desplaza hacia al valor en x obtenido.
    - Terminado esto, indica que el siguiente valor de voltaje recibido corresponderá al otro potenciómetro.
- Por último, si no se han terminado aún las posiciones que podemos asignar a las vallas, se asignan las siguientes posiciones.
- Si hubiesen terminado las posiciones que podemos asignar, se guarda toda la información recolectada sobre la examinación para su auditoría, y cierra el programa de forma automática

### ```gui```

Consiste en un único programa que inicializa una interfaz gráfica; según el botón que se pulse, se ejecuta un programa de examinación u otro.

Utiliza la librería GTK-4 internamente como librería de interfaz de usuario.

### ```utils```

Aquí se implementan funciones auxiliares en los que se apoyan las examinaciones para realizar sus acometidos

#### ```serial.cpp```

Este programa se encarga de proporcionar configuraciones, y métodos para configurar un dispositivo serial, leer de este, y mandar información a través de este; asume que el dispositivo del que lee y escribe ejecuta el sistema software https://github.com/PabloLuisMolinaBlanes/ProyectoTFG/tree/main/Embedded/Integrated/FOSSPsychotechnicalExamination_embedded