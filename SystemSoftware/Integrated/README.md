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

#### ```second_examination.cpp```

### ```utils```

Aquí se implementan funciones auxiliares en los que se apoyan las examinaciones para realizar sus acometidos

#### ```serial.cpp```
