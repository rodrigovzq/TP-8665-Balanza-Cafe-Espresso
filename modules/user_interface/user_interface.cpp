//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "load_cell.h"
#include "espresso_scale.h"
#include "keypad.h"
#include "display.h"
#include "microphone.h"
#include <string.h>
#include <cstring>

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 200
#define SOUND_TRIGGER_THRESHOLD 0.9

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut incorrectCodeLed(LED3);
DigitalOut micLed(LED2);
DigitalOut timerLed(LED1);
DigitalIn timerButton(BUTTON1);
AnalogIn keypad(A1);

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

void pcSerialComStringWrite( const char* str )
{
    uartUsb.write( str, strlen(str) );
}

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============


static bool timerRunning = false;
static clock_t startTime = 0;
static clock_t elapsedTime = 0;
static float botonesLectura = 0.77500;

using namespace std::chrono;

Timer t;

triggerState_t triggerState;
unit_t unitState;

//=====[Declaration and initialization of private global variables]============


//=====[Declarations (prototypes) of private functions]========================


static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================
void timerUpdate() {


    if (timerRunning){
        timerLed=ON;
    }else{
        timerLed=OFF;
    }
    switch (triggerState){

        case TRIGGER_BUTTON:
             if (timerButton==ON){ //si apreto el boton de timer
                if(!timerRunning){
                    timerRunning=true;
                    t.start();
                }
                else{
                    timerRunning=false;
                    t.stop();
                }
                while(timerButton==ON){ //debounce

                }
            }
        break;
        case TRIGGER_MIC:
            int x;
            if(micAnalogRead()>SOUND_TRIGGER_THRESHOLD){
                if(!timerRunning){
                    timerRunning=true;
                    t.start();
                }
            }
            if(timerButton==ON && timerRunning){
                triggerState=TRIGGER_BUTTON;
                timerRunning=false;
                t.stop();
                while(timerButton==ON){ //debounce
                }
            }
            break;

        case TRIGGER_EXT:
            int y;
            // if(micDigitalRead()){
            //     if(!timerRunning){
            //         timerRunning=true;
            //         t.start();
            //     }
            // }
            // if(timerButton==ON && timerRunning){
            //     timerRunning=false;
            //     t.stop();
            //     while(timerButton==ON){ //debounce
            //     }
            // }
            break;
            
    }
    const char * botonPresionado = obtenerBotonPresionado(botonesLectura);
    if(!strcmp(botonPresionado, "DOWN ")){
        timerRunning=false;
        t.reset();

    }
   
} 
void loadCellUpdate(const char * botonPresionado) {
    if(!strcmp(botonPresionado, "RIGHT")){
        tare();
    }
}

void triggerUpdate(const char * botonPresionado){
    if (triggerState == TRIGGER_MIC){
        micLed=ON;
    }else{
        micLed=OFF;
    }
    if(!strcmp(botonPresionado, "UP")){
        switch (triggerState){

            case TRIGGER_BUTTON:
                triggerState = TRIGGER_MIC;
            break;
            case TRIGGER_MIC:
                triggerState = TRIGGER_BUTTON;

            break;
            case TRIGGER_EXT:
                triggerState = TRIGGER_BUTTON;
            break;
        }
    delay(700);
    }


}

void unitUpdate(const char * botonPresionado){

    if(!strcmp(botonPresionado, "LEFT ")){
        switch (unitState){

            case UNIT_GR:
                unitState=UNIT_OZ;
                delay(700);
            break;
            case UNIT_OZ:
                unitState=UNIT_GR;
                delay(700);
            break;
        }
    
    }


}
void userInterfaceInit()
{
    triggerState = TRIGGER_BUTTON;
    unitState = UNIT_GR;
    timerButton.mode(PullDown);
    userInterfaceDisplayInit();
    loadCellInit();
}

void userInterfaceUpdate()
{
    botonesLectura =keypad.read();
    const char * botonPresionado = obtenerBotonPresionado(botonesLectura);
    triggerUpdate(botonPresionado);
    unitUpdate(botonPresionado);
    timerUpdate();
    loadCellUpdate(botonPresionado);
    userInterfaceDisplayUpdate();
    char aux[10]="";
    
    sprintf(aux,"%f\n",botonesLectura);
    pcSerialComStringWrite(botonPresionado);    
    
    
}




//=====[Implementations of private functions]==================================


static void userInterfaceDisplayInit()
{
    displayInit( DISPLAY_CONNECTION_GPIO_4BITS );

}

static void userInterfaceDisplayUpdate()
{
  static int accumulatedDisplayTime = 0;
    char loadCellString[20] = "";
    char tiempoStr[50]; // Cadena para almacenar el tiempo convertido a string
    char aux[5]="";
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;
        switch (unitState){

            case UNIT_GR:
                sprintf(loadCellString, "%0.1f gr         ", loadCellReadGr());
            break;
            case UNIT_OZ:
                sprintf(loadCellString, "%0.1f oz         ", loadCellReadOz());
            break;
        }
        displayCharPositionWrite(14,1);
        if (triggerState == TRIGGER_MIC){
            displayStringWrite("*");
        }else{
            displayStringWrite(" ");
        }
        displayCharPositionWrite ( 0,0 );
        displayStringWrite( loadCellString );


        const char* botonPresionado = obtenerBotonPresionado(botonesLectura);
        unsigned long long int tiempoMili = duration_cast<milliseconds>(t.elapsed_time()).count();
        displayCharPositionWrite ( 0,1 );
        if (tiempoMili){
            
            sprintf(tiempoStr, "%.3f s", (float) tiempoMili/1000);
            displayStringWrite( tiempoStr );
        } else{
            displayStringWrite( "         " );
        }





    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}



