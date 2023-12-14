# Balanza de Espresso


La Balanza de Espresso es un proyecto desarrollado como parte del curso de Sistemas Embebidos de la Facultad de Ingeniería de la Universidad de Buenos Aires. Se trata de un sistema para monitorear y controlar la extracción de café, implementado con mBed OS utilizando una placa de desarrollo STM32 Nucleo-144 F429ZI.

El trabajo realizado se puede encontrar en el siguiente [repositorio](https://github.com/rodrigovzq/TP-8665-Balanza-Cafe-Espresso).

[Informe y documentación (Español)](https://docs.google.com/document/d/1xR8d33nB204xfPZBuqeo-6JVirNfL664zVjjxDgtIDQ)

[Definición de requisitos y casos de uso (Español)](https://docs.google.com/document/d/1Uhc1wMUjK7MCsgxFGO7MmqkpfUsGfbqWiZxKh6JSXM0/)

## Descripción 

La balanza para espresso cuenta con capacidades de medición de peso y tiempo simultáneas, un dispositivo único en su tipo en el mercado actual. Se abordó la necesidad de una herramienta precisa y versátil para la preparación de café espresso, considerando la importancia crítica de controlar tanto el peso como el tiempo durante el proceso de extracción. Se exploraron y compararon productos existentes en el mercado, resaltando la singularidad de este proyecto al incorporar múltiples modos de activación, incluyendo micrófono y puertos externos para una amplia adaptabilidad.
El desarrollo se enfocó en la integración de una máquina de estado en el firmware, permitiendo la selección y cambio dinámico de modos de activación, un aspecto distintivo que no se encuentra en otras balanzas disponibles. Se detallaron pruebas funcionales del hardware y firmware, demostrando la eficacia y precisión de las mediciones. Se identificaron áreas de mejora, incluyendo el diseño de una carcasa resistente para su uso en entornos de cocina y la ampliación potencial del producto para su implementación en máquinas de espresso comerciales, indicando claramente los pasos a seguir para futuros desarrollos.

## Estructura del Repositorio

El repositorio está estructurado de la siguiente manera:

    .
   
    ├── modules
    │   ├── display
    │   ├── keypad
    │   ├── espresso_scale
    │   ├── load_cell
    │   ├── microphone
    │   ├── user_interface
    │   └── ...
    ├── main.cpp
    ├── README.md
    └── ...

Donde se encuentran las carpetas o archivos:

- `modules/`: archivos fuente de los diferentes módulos que forman parte del programa del sistema.
- `main.cpp`: archivo fuente principal del programa del sistema.
- `README.md`: este archivo README.
- Otros archivos como licencia, archivos de configuración de mBed OS, etc.



## Contribución

¡Siéntete libre de contribuir al proyecto! Abre un issue si encuentras problemas o envía un pull request con mejoras y nuevas características.

## Contacto

Para más información o preguntas, contáctame en [rvazquez@fi.uba.ar](mailto:rvazquez@fi.uba.ar).

¡Gracias por tu interés en este proyecto!
