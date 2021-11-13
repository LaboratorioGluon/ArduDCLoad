
#include "rotary.h"

#include <Arduino.h>


#define ROTARY_A 2
#define ROTARY_B 3
#define ROTARY_SWITCH 

#define MIN_PERIOD 10

uint32_t rotaryContador;
uint32_t rotaryLastMillis;

void intRotaryA(){
    if( millis() > (rotaryLastMillis + MIN_PERIOD)){
        rotaryContador++;
        rotaryLastMillis = millis();
    }
    
}


void rotaryConfigure(){
    rotaryContador = 0;
    rotaryLastMillis = millis();
    pinMode(ROTARY_A, INPUT_PULLUP);
    pinMode(ROTARY_B, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(ROTARY_A),intRotaryA,CHANGE);

}

