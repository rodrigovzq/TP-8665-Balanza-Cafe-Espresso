//=====[#include guards - begin]===============================================

#ifndef _KEYPAD_H
#define _KEYPAD_H


//=====[Declaration of public defines]=========================================
#define VALOR_VACIO 0.99
#define VALOR_SET_INFERIOR 0.8
#define VALOR_SET_SUPERIOR 0.99
#define VALOR_LEFT_INFERIOR 0.6
#define VALOR_LEFT_SUPERIOR 0.80
#define VALOR_DOWN_INFERIOR 0.3
#define VALOR_DOWN_SUPERIOR 0.6
#define VALOR_UP_INFERIOR 0.2
#define VALOR_UP_SUPERIOR 0.3
#define VALOR_RIGHT 0.2

//=====[Declaration of public data types]======================================
// Enumeración para representar los botones
typedef enum {
    BOTON_SET,
    BOTON_VACIO,
    BOTON_LEFT,
    BOTON_DOWN,
    BOTON_UP,
    BOTON_RIGHT,
    BOTON_DESCONOCIDO
} boton_t;

//=====[Declarations (prototypes) of public functions]=========================
boton_t obtenerBotonPresionado(float lectura);
//=====[#include guards - end]=================================================

#endif // _KEYPAD_H