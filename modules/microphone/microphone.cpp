//=====[Libraries]=============================================================

#include "mbed.h"

#include "microphone.h"

#include "espresso_scale.h"

//=====[Declaration and initialization of public global objects]===============

DigitalIn dMic(D12);

AnalogIn aMic(A0);

float micAnalogRead(){
    return aMic.read();
}

int micDigitalRead() { 
       return dMic;
}