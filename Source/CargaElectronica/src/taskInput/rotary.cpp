#include <Arduino.h>
#include "globalConfig.h"
#include "taskInput/rotary.h"



#define DEADZONE_TIME_MS 10

uint32_t rotaryContador;
uint32_t rotaryLastMillis;

void intRotaryA(){
    if( millis() > (rotaryLastMillis + DEADZONE_TIME_MS)){
        rotaryContador++;
        rotaryLastMillis = millis();
    }
    
}


void rotaryConfigure(){

    // Rotay encoder configuration
    rotaryContador = 0;
    rotaryLastMillis = millis();
    pinMode(INPUT_ROTARY_PIN_A, INPUT_PULLUP);
    pinMode(INPUT_ROTARY_PIN_B, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(INPUT_ROTARY_PIN_A),intRotaryA,CHANGE);


    // Rotary encoder switch configuration
    pinMode(INPUT_ROTARY_PIN_SWITCH, INPUT_PULLUP);

}

uint8_t getRotaryPushState(){

    // TODO: Change it to PORT registers
    if(digitalRead(INPUT_ROTARY_PIN_SWITCH) == LOW){
        return true;
    }else{
        return false;
    }

}

uint32_t getRotaryCounter(){
    uint32_t currentRotaryCounter = rotaryContador;
    rotaryContador = 0;
    return currentRotaryCounter;
}


