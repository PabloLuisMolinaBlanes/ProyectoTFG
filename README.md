# FOSS Psychotechnical Examination

## Introducción

Este proyecto es mi Trabajo de Fin de Grado de la Universidad de Málaga. Ha sido implementado por Pablo Luis Molina Blanes; estudiante en su último año en el Grado de Ingeniería del Software.

El proyecto se estructura como un monorepo donde se desarrollan cinco proyectos de forma paralela al mismo tiempo; los cuales forman los componentes del proyecto, que en su conjunto, se denomina *FOSS Psychotechnical Examination*.

## FAQ

### ¿Qué tecnologías se utilizan en este proyecto?

En general, es un proyecto muy variado con respecto a tecnologías; de forma general, se utilizan las siguientes tecnologías:

- Se utiliza el lenguaje C y el framework ESP-IDF para los programas que corren en el microcontrolador ESP32; la interfaz gráfica que permite seleccionar examinaciones también se ha implementado en C, bajo la librería GTK-4.

- Se utiliza C++ para la implementación de las examinaciones psicotécnicas en si que corrren fuera de los microcontroladores; también se utiliza para implementar una librería de coumniación con dispositivo serial.

- Se utiliza TypeScript para la implementación de servidores en nube y cliente local.

- Se utiliza MySQL como gestor de base de datos para almacenar información relativa a examinados y sus resultados

Más información específica sobre tecnologías se puede encontrar en los ficheros ```README.md``` de los proyectos correspondientes.

### ¿Hay algún script que permita hacer build automáticamente?

No he desarrollado ningún script automatizado a tal efecto; aún así, para cada proyecto, se pueden encontrar instrucciones de compilación y despliegue en su ```README.md``` correspondiente; pero son instrucciones a ejecutar de forma manual.

### ¿Por qué no puedo compilar/ejecutar este proyecto? Me salen mensajes de error.

Primero, me gustaría empezar con algo muy importante; este proyecto ha sido desarrollado para una arquitectura hardware y software muy específica y concreta, puedes encontrar más información en la sección **Arquitectura software y hardware**; es posible que no tengas los requisitos necesarios para poder correr el proyecto.

De todas formas, he comprobado personalmente que con las dependencias correctas, debería cada componente por lo menos compilar bien en cualquier sistema operativo GNU/Linux recitente; si aparece algún mensaje de error, asegurate que no te falta ninguna dependencia que haga falta para compilar los archivos.

### ¿Es este proyecto a fines legales un dispositivo médico?

No, ni se ha certificado como tal; y muy probablemente no cumpla los estándares a tal efecto; busca ser un prototipo que se pueda adaptar, no un dispositivo médico certificado.

No me hago responsable si un tercero intenta hacer un uso indebido de este proyecto tal cual como dispositivo médico.

### ¿Se ha utilizado IA Generativa para crear este proyecto?

No he utilizado IA generativa de forma deliberada para realizar ninguna parte de este proyecto; esto incluye documentación, código fuente, y parámetros de configuración o construcción.

Aún así, utilizo librerías externas, hay algunas porciones de código fuente que han sido tomadas de Internet, y he consultado documentación externa; desconozco su provenencia, y por ende, no puedo asegurar que no haya habido IA generativa involucrada en su creación.

### ¿Qué es este proyecto?

En resumen, es un suite software que busca implementar un sistema software de examinación médica para conductores bajo licencias permisivas.

Todos los componentes desarrollados por mí en este proyecto se licencian bajo la licencia MIT.

## Arquitectura software y hardware

### Arquitectura software

La arquitectura software la podemos dividir en dos secciones, las cuales no están conectadas entre sí y funcionan de forma independiente.

#### Arquitectura de software de aplicación local (Carpetas Embedded y SystemSoftware)

Esta arquitectura comunica a dos dispositivos, un ordenador, y un microcontrolador entre sí a través de un cableado serial.

El software localizado en el ordenador se encarga de inicializar parámetros, ejecutar la lógica relativa a cada examinación en pantalla, y a almacenar los datos de las examinaciones que se hagan. Recibe información del dispositivo empotrado a tales efectos.

El software empotrado se encarga de recoger los datos de dispositivos electrónicos con los que interactua el usuario para ejecutar las examinaciones psicotécnicas a las que se somete. 

#### Arquitectura cliente-servidor local (Carpetas Web y Cloud)

Esta arquitectura comunica un cliente local ejecutado en un ordenador; y un servidor remoto desplegado en una nube externa.

El software en el ordenador se encarga de procesar, validar, y enviar datos al servidor remoto relativos a examinaciones específicas, de forma segura.

El software en nube externa se encarga de almacenar y enviar información a los clientes locales según las peticiones que estos realizen.

### Arquitectura hardware

Se asume la siguiente arquitectura hardware:

- Un dispositivo Raspberry Pi, comunicado por cable de datos USB a un dispositivo ESP-32.
- Un dispositivo UART interno, es decir, no externo (es dispositivo externo si este se conecta explícitamente a los pines RX y TX del microcontrolador)
- Un botón electrónico
- Dos potenciómetros lineales.
- Suficiente cableado para interconectar todos los dispositivos electrónicos con el microcontrolador ESP-32.

## Instrucciones de compilación y despliegue

No hay instrucciones para desplegar o compilar el proyecto completo en sí; el usuario debe acceder a cada componente individual, y ejecutar las instrucciones a tal efecto en su ```README.md``` correspondiente.

## Componentes del proyecto

Este proyecto se compone de cinco partes distintas (sin incluir SanityTests, que sirven para comprobar aspectos básicos de ejecución)

- Embedded: Embedded es el proyecto que implementa la parte relativa a sistemas empotrados del proyecto.
- SystemSoftware: SystemSoftware es el proyecto que implementa la parte relativa a software de sistemas local del proyecto.
- Cloud: Cloud es el proyecto que implementa la parte relativa a servidores nube del proyecto.
- Web: Web es el proyecto que implementa la parte relativa a clientes locales del proyecto.
- Memoria: Es la memoria de trabajo de este proyecto; bajo la plantilla ofrecida en LaTeX por la Universidad de Málaga.

La carpeta principal de cada proyecto en sí es la carpeta denominada ```Integrated```; la carpeta ```Spikes``` es una carpeta secundaria relativa a implementaciones incrementales de porciones específicas de los proyectos.