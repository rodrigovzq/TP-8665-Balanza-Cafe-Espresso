//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "espresso_scale.h"
#include "user_interface.h"
#include "keypad.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void espressoScaleInit()
{
    userInterfaceInit();
    //fireAlarmInit();
    //pcSerialComInit();
}

void espressoScaleUpdate()
{
    userInterfaceUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
