# Memoria de trabajo

Este es el repositorio relativo a los archivos de la memoria de trabajo realizados por Pablo Luis Molina Blanes.

# Instrucciones de compilación y lectura

Antes que nada, se debe instalar una distribución LaTeX en el sistema si no se dispone de una.

Una distribución que recomiendo personalmente es [TeX Live](https://www.tug.org/texlive/)

Tras hacer esto, se ha de acceder al repositorio raiz de esta memoria, y ejecutar los siguientes comandos en orden:

```
xelatex main
biber main
xelatex main
xelatex main
```

Aparecerán muchos archivos auxiliares de compilación y un archivo denominado ```main.pdf```, en formato PDF (Portable Document Format). Es en este archivo donde se puede leer una versión renderizada en cualquier lector de archivos PDF.

# Descripción por capítulo

## Marco teórico

En el marco teórico se expone y se describe y se acreditan los temas, campos del saber, y técnicas más relevantes y utilizadas para FOSS Psychotechnical Examination.

Aquí se introduce una colección de técnicas matemáticas, psicológicas y de desarrollo software; además del contexto legal y social de herramientas de evaluación psicotécnica.

## Análisis

En la sección de análisis nos introducimos a las funcionalidades de cada componente de FOSS Psychotechnical Examination. Busca ser una colección resumida de las funcionalidades más importantes para el correcto funcionamiento del suite software.

## Diseño

En esta sección se expone la arquitectura de la suite software en general; y de todos sus componentes individuales. También se entra en detalle en la arquitectura y decisiones relativa a hardware y dispositivos electrónicos utilizados en el proyecto.

## Implementación

En esta sección se describen y desarrollan los flujos de ejecución principales de la aplicación, desarrollados paso a paso y con explicaciones varias.

## Funcionamiento

En esta sección se introducen los roles que pueden tomar los usuarios de la aplicación; se han incluido roles tradicionales como el del usuario o el del doctor; y también se ha incluido aquí el rol de atacante para enfatizar posibles intentos de ataque, y protecciones otorgadas por la suite software ante estos ataques

## Pruebas

Aquí se describen las tecnologías de pruebas que se han utilizado para cada componente de esta suite software; además de las pruebas realizadas, su razonamiento, y los resultados esperados.

## Conclusiones

Aquí se da una recolección de lo aprendido y realizado en este proyecto; desde el ángulo de vista de la retrospectiva.

## Anexos

Aquí se introducen documentos explicativos, que sirven para desarrollar aspectos no fácilmente desarrollables como secciones dentro del documento de la memoria; se incluye un manual de usuario, un manual de instalación, y un modelo de formulario de consentimiento para el tratamiento de los datos de usuarios.