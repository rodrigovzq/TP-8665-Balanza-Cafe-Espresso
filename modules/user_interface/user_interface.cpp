//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "code.h"
#include "siren.h"
#include "espresso_scale.h"
#include "fire_alarm.h"
#include "date_and_time.h"
#include "temperature_sensor.h"
#include "gas_sensor.h"
#include "keypad.h"
#include "display.h"
#include <string.h>
#include <cstring>

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 100

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut incorrectCodeLed(LED3);
DigitalOut systemBlockedLed(LED2);
DigitalOut timerLed(LED1);
DigitalIn timerButton(BUTTON1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

char codeSequenceFromUserInterface[CODE_NUMBER_OF_KEYS];

static bool timerRunning = false;
static clock_t startTime = 0;
static clock_t elapsedTime = 0;
static float botonesLectura = 0.77500;

using namespace std::chrono;

Timer t;

//=====[Declaration and initialization of private global variables]============

static bool incorrectCodeState = OFF;
static bool systemBlockedState = OFF;

static bool codeComplete = false;
static int numberOfCodeChars = 0;

//=====[Declarations (prototypes) of private functions]========================

static void userInterfaceMatrixKeypadUpdate();
static void incorrectCodeIndicatorUpdate();
static void systemBlockedIndicatorUpdate();

static void userInterfaceDisplayInit();
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================
void timerUpdate(const char * botonPresionado) {

    if (timerButton==ON){ //si apreto el boton de SET
        if(!timerRunning){
            timerRunning=true;
            t.start();
        }
        else{
            timerRunning=false;
            t.stop();
        }
        while(timerButton==ON){

        }
    }
    if(!strcmp(botonPresionado, "DOWN ")){
        timerRunning=false;
        t.reset();

    }
   
} 
void userInterfaceInit()
{
    incorrectCodeLed = OFF;
    systemBlockedLed = OFF;
    timerButton.mode(PullDown);
    //matrixKeypadInit( SYSTEM_TIME_INCREMENT_MS );
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    botonesLectura =temperatureSensorReadCelsius();
    const char * botonPresionado = obtenerBotonPresionado(botonesLectura);

    timerUpdate(botonPresionado);
    //userInterfaceMatrixKeypadUpdate();
    //incorrectCodeIndicatorUpdate();
    //systemBlockedIndicatorUpdate();
    userInterfaceDisplayUpdate();
    if (timerRunning){
        timerLed=ON;
    }else{
        timerLed=OFF;
    }
}

bool incorrectCodeStateRead()
{
    return incorrectCodeState;
}

void incorrectCodeStateWrite( bool state )
{
    incorrectCodeState = state;
}

bool systemBlockedStateRead()
{
    return systemBlockedState;
}

void systemBlockedStateWrite( bool state )
{
    systemBlockedState = state;
}

bool userInterfaceCodeCompleteRead()
{
    return codeComplete;
}

void userInterfaceCodeCompleteWrite( bool state )
{
    codeComplete = state;
}


//=====[Implementations of private functions]==================================

static void userInterfaceMatrixKeypadUpdate()
{
    // static int numberOfHashKeyReleased = 0;
    // char keyReleased = matrixKeypadUpdate();

    // if( keyReleased != '\0' ) {

    //     if( sirenStateRead() && !systemBlockedStateRead() ) {
    //         if( !incorrectCodeStateRead() ) {
    //             codeSequenceFromUserInterface[numberOfCodeChars] = keyReleased;
    //             numberOfCodeChars++;
    //             if ( numberOfCodeChars >= CODE_NUMBER_OF_KEYS ) {
    //                 codeComplete = true;
    //                 numberOfCodeChars = 0;
    //             }
    //         } else {
    //             if( keyReleased == '#' ) {
    //                 numberOfHashKeyReleased++;
    //                 if( numberOfHashKeyReleased >= 2 ) {
    //                     numberOfHashKeyReleased = 0;
    //                     numberOfCodeChars = 0;
    //                     codeComplete = false;
    //                     incorrectCodeState = OFF;
    //                 }
    //             }
    //         }
    //     }
    // }
}

static void userInterfaceDisplayInit()
{
    displayInit( DISPLAY_CONNECTION_GPIO_4BITS );
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Peso:" );

   // displayCharPositionWrite ( 0,1 );
   // displayStringWrite( "Tiempo:" );
}

static void userInterfaceDisplayUpdate()
{
  static int accumulatedDisplayTime = 0;
    char temperatureString[8] = ""; //TODO: Reemplazar temperature por buttonkeypad
    char tiempoStr[50]; // Cadena para almacenar el tiempo convertido a string
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;
        botonesLectura =temperatureSensorReadCelsius();

        
        sprintf(temperatureString, "%.5f", temperatureSensorReadCelsius()); // TODO: reemplazar por lectura de
        displayCharPositionWrite ( 5,0 );
        displayStringWrite( temperatureString );
        displayCharPositionWrite ( 11,0 );
        displayStringWrite( " gr" );

        const char* botonPresionado = obtenerBotonPresionado(botonesLectura);
        unsigned long long int tiempoMili = duration_cast<milliseconds>(t.elapsed_time()).count();
        if (tiempoMili){
            sprintf(tiempoStr, "Tiempo: %.3f s", (float) tiempoMili/1000);
            displayCharPositionWrite ( 0,1 );
            displayStringWrite( tiempoStr );
        } else{
            displayCharPositionWrite ( 0,1 );
            displayStringWrite( "                " );
        }





    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}

static void incorrectCodeIndicatorUpdate()
{
    incorrectCodeLed = incorrectCodeStateRead();
}

static void systemBlockedIndicatorUpdate()
{
    systemBlockedLed = systemBlockedState;
}