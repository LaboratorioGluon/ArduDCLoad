#include <Arduino.h>
#include <RotaryEncoder.h>


#include "globalConfig.h"
#include "taskInput/rotary.h"

#define readA bitRead(PIND,2)
#define readB bitRead(PIND,3)

#define DEADZONE_TIME_US 400


RotaryEncoder encoder(2, 3, RotaryEncoder::LatchMode::FOUR3);

uint32_t rotaryContador;
uint32_t rotaryLastMillis;

void intRotaryAA(){
    if( micros() > (rotaryLastMillis + DEADZONE_TIME_US)){
        if(readA){
            rotaryContador+=readB? 1:-1;
        }else{
            rotaryContador+=readB?-1: 1;
        }
        rotaryLastMillis = micros();
    } 
}

void intRotaryA(){
    if( millis() > (rotaryLastMillis + DEADZONE_TIME_US)){
        rotaryContador--;
        rotaryLastMillis = millis();
    } 
}

void intRotaryB(){
    if( millis() > (rotaryLastMillis + DEADZONE_TIME_US)){
        rotaryContador++;
        rotaryLastMillis = millis();
        
    } 
}


void rotaryConfigure(){
    
    // Rotay encoder configuration
    rotaryContador = 0;
    rotaryLastMillis = millis();
    
    // Rotary encoder switch configuration
    pinMode(INPUT_ROTARY_PIN_SWITCH, INPUT_PULLUP);

    return;
    // This is done internally by the library
    pinMode(INPUT_ROTARY_PIN_A, INPUT_PULLUP);
    pinMode(INPUT_ROTARY_PIN_B, INPUT_PULLUP);

    //attachInterrupt(digitalPinToInterrupt(INPUT_ROTARY_PIN_A),intRotaryAA,CHANGE);
    //attachInterrupt(digitalPinToInterrupt(INPUT_ROTARY_PIN_B),intRotaryB,FALLING);

    

}


void rotaryTick(){
    encoder.tick();

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

#if 0
    static int pos = 0;

    cnt++;
    
    int newPos = encoder.getPosition();
    if (pos != newPos) {
        Serial.println(newPos);
        pos = newPos;
    } 
    cnt =0;
    
    
    return 0;
#endif
    static int currentRotaryCounter;
    static int lastPos = 0;
    
    int newPos = encoder.getPosition();

    if(newPos != lastPos){
        Serial.println("New pos:" + String(newPos));
    }

    currentRotaryCounter = newPos - lastPos;
    lastPos = newPos;
    return currentRotaryCounter;
}


