//=====[Libraries]=============================================================

#include "mbed.h"

#include "microphone.h"

#include "espresso_scale.h"

//=====[Declaration and initialization of public global objects]===============


AnalogIn aMic(A0);


static long read_average(int times) {
	long sum = 0;
	for (int i = 0; i < times; i++) {
		sum += aMic.read();
	}
	return sum / times;
}


float micAnalogRead(){
    return aMic.read();
}

bool micDigitalRead() { 
    return read_average(5) > 0.5;
}

