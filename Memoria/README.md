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