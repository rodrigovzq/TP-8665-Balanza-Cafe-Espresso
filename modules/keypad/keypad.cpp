//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "keypad.h"

const char* obtenerBotonPresionado(float lectura) {
    if (lectura > 0.99) {
        return "SET ";
    } else if (lectura > 0.8 && lectura <= 0.99000) {
        return "     ";
    } else if (lectura >= 0.6 && lectura <= 0.80) {
        return "LEFT ";
    } else if (lectura >= 0.3 && lectura < 0.6) {
        return "DOWN ";
    } else if (lectura >= 0.2 && lectura < 0.3) {
        return "UP";
    } else if (lectura >= 0 && lectura < 0.2) {
        return "RIGHT";
    } else {
        return "?";
    }
}