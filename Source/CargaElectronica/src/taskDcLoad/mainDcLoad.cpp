#include "taskDcLoad/mainDcLoad.h"
#include "taskInput/mainInput.h"
#include "globalConfig.h"
#include <Arduino.h>

constexpr unsigned long dcLoadPeriodMs = 100; // 100ms 

namespace taskDcLoad {


    unsigned long lastMillis;
    unsigned long dt;

    void internalLoop(unsigned long deltaTime);

    void dcLoadInitialize(){

        pinMode(9,155);
        TCCR1B = (TCCR1B & B11111000) | B00000010; // for PWM frequency of 31372.55 Hz

        pinMode(DCLOAD_FAN_OUTPUT_PIN, OUTPUT);

    }


    void dcLoadMainLoop(){

        // Calculate the time since the last call
        dt = millis() - lastMillis;

        if(dt > dcLoadPeriodMs){
            //Serial.print("Executing DcLoad Main Loop!");Serial.println(millis());
            lastMillis = millis();

            internalLoop(dt);

        }

    }

    void internalLoop(unsigned long deltaTime){

        if(taskInput::inputOutData.switchOk == LOW){
            digitalWrite(DCLOAD_FAN_OUTPUT_PIN, HIGH);
        }else{
            digitalWrite(DCLOAD_FAN_OUTPUT_PIN, LOW);
        }


    }
    

};