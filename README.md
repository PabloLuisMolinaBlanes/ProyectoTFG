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

### ¿Qué es este proyecto?

En resumen, es un suite software que busca implementar un sistema software de examinación médica para conductores bajo licencias permisivas.

Todos los componentes desarrollados por mí en este proyecto se licencian bajo la licencia MIT.

## Arquitectura software y hardware


## Instrucciones de compilación y despliegue

No hay instrucciones para desplegar o compilar el proyecto completo en sí; el usuario debe acceder a cada componente individual, y ejecutar las instrucciones a tal efecto en su ```README.md``` correspondiente.

## Componentes del proyecto
