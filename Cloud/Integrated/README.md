# FOSSPsychotechnicalExamination - Parte cloud

## Introducción

Este programa implementa los programas del proyecto FOSSPsychotechnicalExamination que se ejecutan en el servidor Cloud

Para leer más sobre FOSSPsychotechnicalExamination, consúltese el documento README.md en el fichero raiz del proyecto.

## FAQ

### ¿Qué tecnologías utiliza este proyecto?

Este proyecto utiliza Node.js, junto con las librerías Typescript, Express y Prisma principalmente.

- Node.js es un entorno de ejecución para JavaScript; fuera del navegador, donde habitualmente se ejecuta.
- Typescript es un lenguaje de programación que agrega tipado a JavaScript. Este código se puede traducir a JavaScript.
- Express es una librería para realizar APIs REST.
- Prisma es un ORM (Object Relational Manager) que transforma objetos de JavaScript a un formato relacional; esto es bastante útil para poder utilizar métodos JavaScript para realizar funcionalidades en una base de datos sin tener que crear peticiones SQL directamente.

### ¿Por qué es tan minimalista, por qué no hacer un CRUD completo?

Sobre todo porque no es necesario.

En este tipo de sistemas en nube médicos es necesario reducir bastante la superficie de ataque lo más posible; dar más funcionalidad de la necesaria lo único que consigue es abrir las puertas a posibles atacantes, y no proporcionan valor a nuestros usuarios.

Desde el cliente local, por defecto, siempre se mandan los datos personales de forma encriptada; sin los parámetros de encriptación originales; no se puede obtener información relevante de los usuarios. Solo se han realizado métodos de lectura, y de escritura; no podemos eliminar ni modificar datos desde este servidor.

#### ¿El que no podamos borrar o modificar desde el servidor no incumpliría la Protección de Datos?

No tiene porque, desde la base de datos se puede establecer una política, por ejemplo, que no pueden existir filas en esta con más de 10 años (el máximo periodo legal en España para obtener una revisión médica).

Que el servidor de aplicación no deje modificar o borrar los datos no quiere decir que no se puedan modificar o borrar datos en general en la base de datos.

De todas formas, eso no entra dentro de los parámetros de este prototipo, que busca ser más a fin demostrativo; y no soy abogado, por lo que esto no constituye aviso legal.


## Instrucciones de traducción y ejecución

### Advertencia 

Por defecto, el Dockerfile asume un usuario root con clave root, esto es muy inseguro, y solo se muestra en este repositorio así con fines demostrativos; al utilizar este programa, se debería modificar la clave proporcionada por defecto, y además, evitar utilizar el usuario root en la medida de lo posible. 

### Instrucciones de instalación local/en máquina virtual

1. Descarga e instala [Docker Engine](https://docs.docker.com/engine/install/)
2. Comprueba que también se incluye Docker Compose.
3. Ejecuta el comando ```docker compose -f compose.yaml build --no-cache```
4. Ejecuta el comando ```docker compose -f compose.yaml up```

Compruebe que el backend se encuentra en http://localhost:<PUERTO_DE_BACKEND>


### Instrucciones de instalación en un servidor web Nginx

1. Siga las instrucciones de máquina local.
2. Acceda a su fichero de configuración nginx
- En Linux, se suele encontrar en la ruta ```/etc/nginx/sites-available/```
3. Incluya el siguiente parámetro dentro de su bloque ```server``` preferido:
```{nginx}
location <ruta> {
		proxy_pass <protocolo_http_o_https>://127.0.0.1:<puerto de servidor>;
} 
```
4. Compruebe que su configuración sigue siendo válida con el comando ```nginx -t```
5. Reinicie el servidor ```service nginx reload```

Compruebe que el servidor se encuentra en <protocolo_http_o_https>://<ip_de_maquina>:<puerto_de_escucha_de_nginx>

## Componentes del programa

Este programa se compone de dos contenedores; los cuales a su vez, se componen de varios componentes lógicos

### Contenedor de bases de datos

Este contenedor utiliza el gestor de bases de datos MySQL, y por defecto instala su última versión disponible en el Docker Hub.

Por defecto, se inicializa un usuario *root* con clave *root*; y se inicia un esquema con un hospital de ejemplo; con los siguientes parámetros con carácter demostrativo:
- Usuario: HOSPITAL_MARIA_CRISTINA
- Clave: GatitoPerez

### Contenedor de servidor

Este es un contenedor que por defecto instala NPM, las dependencias del proyecto; e inicializa un servidor que escucha en ```localhost:3000``` por defecto.

Está pensado para que un servidor externo web haga proxy con este servidor; pero si se quiere que el servidor escuche a cualquier dirección IP (o dominio) que le llegue de forma directa, sin proxies, se debería cambiar ```localhost``` por ```0.0.0.0```, o a la IP que se quiera escuchar.

Dispone de varios componentes lógicos:

#### API REST

El API REST implementa un CRUD parcial con funciones de lectura de todos los datos relativos a un hospital en concreto, dado un nombre de hospital y una clave; y una función para agregar una nueva fila a la base de datos.

#### Utilidades

Se incluyen funcionalidades para realizar comparación de contraseñas recibidas con hashes en base de datos.