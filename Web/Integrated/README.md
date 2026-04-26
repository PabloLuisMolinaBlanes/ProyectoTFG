# FOSSPsychotechnicalExamination - Parte cliente local

## Introducción

## FAQ

### ¿Qué tecnologías se utilizaron en este proyecto?

Principalmente Node.js y sus librerías.

- Node.js es un entorno de ejecución para JavaScript; fuera del navegador, donde habitualmente se ejecuta.

### ¿Por qué no lo denominas 'frontend'?

Por que no es exáctamente un frontend; es más cercano a un cliente local CLI.

Normalmente se asocia 'frontend' a una aplicación completa que recibe datos del servidor, y se conecta a este de forma contante y asíncrona; por ejemplo, un frontend puede enrutar hacia un componente, y ese componente realizar una llamada al servidor para pedir datos.

Esta aplicación es más cercana a un cliente local CLI; las llamadas a servidores externo son mínimas, y se han tomado algunas decisiones distintas a lo que se entiende normalmente por frontend.

### ¿Por qué generas un archivo HTML directamente en el ordenador en vez de hacer una interfaz más amigable al usuario?

Principalmente, por motivos de seguridad.

Ejecutar y leer archivos locales desde un navegador web es algo que rompe completamente el modelo de seguridad de qué puede hacer código JavaScript dentro del navegador; y no lo permite para nada hacer; por ello, normalmente, para hacer un frontend 'normal', como con Angular, Svelte, o con un proyecto React generado con Vite, se necesita estar escuchando a un puerto, y abrir un servidor web que pueda ejecutar ese frontend.

En general, queremos reducir al mínimo los puertos a los que está escuchando en todo momento nuestro dispositivo, porque al fin y al cabo, eso son puertas para nuestros atacantes para entrar y robar datos.

Al obtener los datos con una llamada al servidor en nube, y crear un archivo HTML a partir de esos datos; reducimos al mínimo los puertos a los que escucha nuestro dispositivo (el que abre temporalmente el cliente para la conexión TCP con el servidor externo).

## Instrucciones de traducción y ejecución

1. Descarga e instala [Node.JS](https://nodejs.org/en/download)
2. Accede al directorio raiz del proyecto.
3. Ejecuta el comando ```npm install```
4. Ejecuta el comando ```npm run dev```

Debería aparecer la interfaz CLI correctamente.

## Componentes del programa

Este programa se compone de un único archivo, ```client.ts```, con tres divisiones lógicas:

### Recolección de datos de examinación

Hay una opción en el programa que permite recolectar los datos de un examinado; este es el flujo de funcionamiento:

1. Se intenta acceder a tres archivos:
 - ```first_examination.txt```: Con los datos de examinación del primer examen
 - ```second_examination.txt```: Con los datos de examinación del segundo examen
 - ```hospital_credentials.txt```: Con los datos de identificación para el hospital.
2. Si se localizan estos archivos, se empieza preguntando nombre y apellidos del usuario.
3. Después, se pide tipo de documento; puede ser un DNI español, o un número NIE.
4. Se pide el número de documentación escogido, más la letra; se contrasta que el número proporcionado corresponde con la letra proporcionada; si no es así, el número se considera inválido y se lanza un mensaje de error.
5. Se muestra un formulario para confirmar los datos.
6. Se encriptan los datos personales del usuario con unos parámetros de encripción cargados o generados en segundo plano al iniciarse la aplicación; y se envían los datos de examinación al servidor. 

### Obtención de datos de examinación

Esta opción permite obtener los datos de examinación de todos los usuarios examinados dentro del dispositivo; su flujo de funcionamiento es el siguiente:

1. Se intenta acceder a ```hospital_credentials.txt```, un archivo con datos de identificación para el dispositivo asociado a un hospital.
2. Se envía una petición al servidor en nube para que reciba los datos y los envíe al cliente.
3. El cliente genera un archivo HTML, que consiste de una tabla simple donde se muestra toda la información asociada al hospital; y desencriptada por completo.
4. Se escribe el archivo y se cierra el programa.

### Utilidades

Hay muchas utilidades en el programa; hay funciones de lectura de archivos, de cifrado y descifrado, y de validación de datos para números de documentación españoles.