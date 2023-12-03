//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "keypad.h"

boton_t obtenerBotonPresionado(float lectura) {
    if (lectura > VALOR_VACIO) {
        return BOTON_VACIO;
    } else if (lectura > VALOR_SET_INFERIOR && lectura <= VALOR_SET_SUPERIOR) {
        return BOTON_SET;
    } else if (lectura >= VALOR_LEFT_INFERIOR && lectura <= VALOR_LEFT_SUPERIOR) {
        return BOTON_LEFT;
    } else if (lectura >= VALOR_DOWN_INFERIOR && lectura < VALOR_DOWN_SUPERIOR) {
        return BOTON_DOWN;
    } else if (lectura >= VALOR_UP_INFERIOR && lectura < VALOR_UP_SUPERIOR) {
        return BOTON_UP;
    } else if (lectura >= 0 && lectura < VALOR_RIGHT) {
        return BOTON_RIGHT;
    } else {
        return BOTON_DESCONOCIDO;
    }
}
