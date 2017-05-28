# <a href='www.BlackPolp.csta.mx'><img src='http://www.csta.mx/ima/BlackPolp_github_150.png' height='100'></a>

BlackPolp es una herramienta desarrollada en C++ para el control, tratamiento y conversión del color, para el apoyo en el diseño en general.  

BlackPolp proporciona información acerca de cualquier color, incluyendo conversiones a muchos modelos de color (HEX, FFHEX, WEB Safe, RGBA, BGR, RGB%, CMYK, HSL, HSV, XYZ, xyY, LAB y Hunter LAB).

BlackPolp proporciona esquemas sobre los colores en forma de paletas como: Complementarios, Análogos, Divididos, Triaticos y Cuadraticos. También proporciona tonos sobre los colores en forma de las paletas: Similares, Monocromáticos, Variación de Sombra, Variación de Color y Tonos de Color.

BlackPolp tiene la capacidad para descargar, diseñar y trabajar con paletas de colores, puedes descargarlas desde el servicio https://color.adobe.com  y http://colourlovers.com, o crearlas, consultarlas y gestionarlas directamente en la aplicación, además de guardarlas en el formato “Adobe Swatch Exchang (*.ase)” para poder compartirlas y añadirlas a proyectos de Illustrator y Photoshop.

BlackPolp permite cargar o arrastrar y soltar una imagen para extraer los colores más comunes que la componen, así como una paleta con los colores prominentes de la imagen.


## Inicio

En este apartado se explica cómo se puede obtener una compilación funcional de la aplicación para efecto de pruebas.

### Requisitos Previos

Esta aplicación está desarrollada en C++ con el IDE C++Builder XE7 y una librería propietaria y no publica de CSTA. Por ende, se requiere de la instalación de [C++Builder XE7](https://www.embarcadero.com/home) (o superior) en el equipo.

### Instalación

Identifique los archivos:

```.\[OUT]\BlackOcean_early.bpl```<br/>
```.\[OUT]\BlackOcean.bpl```<br/>
```.\[OUT]\BlackOcean_fmx.bpl```

Abra el IDE C++Builder.

Abra la opción del menú: ```Component > Install Packages...```

Ya en la ventana ```Install Packages``` presione el botón ```Add...``` y diríjase al archivo ```.\[OUT]\BlackOcean_early.bpl```

En la ventana ```Install Packages``` presione el botón ```Add...``` y diríjase al archivo ```.\[OUT]\BlackOcean.bpl```

En la ventana ```Install Packages``` presione el botón ```Add...``` y diríjase al archivo ```.\[OUT]\BlackOcean_fmx.bpl```

Presiona el botón ```ok```, y con esto habremos instalado los paquetes necesarios de CSTA.

Abra el archivo ```.\BlackPolp\BlackPolp.cbproj```

A disfrutar.


## Marcos de Trabajo Usados

* [Firemonkey](https://www.embarcadero.com/products/rad-studio/fm-application-platform) - Framework para el pintado de Shape's (formas), d2d.
* [BlackOcean](http://csta.mx) - Framework para el pintado de interfaces enriquecidas, animaciones y otras funciones.


## Autores

* Jesús E. Aldréte Hernández - CSTA


## License

Este proyecto está licenciado bajo la Licencia APACHE 2.0 - Véase el archivo [LICENSE](LICENSE) para más detalles.