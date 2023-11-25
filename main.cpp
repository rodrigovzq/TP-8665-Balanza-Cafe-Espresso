//=====[Libraries]=============================================================

#include "espresso_scale.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    espressoScaleInit();
    while (true) {
        espressoScaleUpdate();
    }
}