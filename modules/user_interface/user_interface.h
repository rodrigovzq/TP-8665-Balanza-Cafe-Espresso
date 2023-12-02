//=====[#include guards - begin]===============================================

#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
    TRIGGER_BUTTON,
    TRIGGER_MIC,
    TRIGGER_EXT
} triggerState_t;

typedef enum{
    UNIT_GR,
    UNIT_OZ
} unit_t;
//=====[Declarations (prototypes) of public functions]=========================

void userInterfaceInit();
void userInterfaceUpdate();
void timerUpdate();
void loadCellUpdate(const char * botonPresionado);
void triggerUpdate(const char * botonPresionado);



//=====[#include guards - end]=================================================

#endif // _USER_INTERFACE_H_