#include <Arduino.h>
#include "taskInput/mainInput.h"
#include "taskInput/rotary.h"

#include "globalConfig.h"

constexpr unsigned long InputPeriodMs = 100; // 100ms 



namespace taskInput {

    unsigned long lastMillis;
    unsigned long dt;


    struct inputData inputOutData;
    
    void inputInitialize(){
        
        pinMode(INPUT_BUTTON_OK_PIN  , INPUT_PULLUP);
        pinMode(INPUT_BUTTON_BACK_PIN, INPUT_PULLUP);

        pinMode(INPUT_VOLTAGE_SENSE_PIN, INPUT);
        analogReference(DEFAULT);
        
        rotaryConfigure();

    }


    void internalLoop(unsigned long deltaTime);

    void inputMainLoop(){

        // Calculate the time since the last call
        dt = millis() - lastMillis;

        if(dt > InputPeriodMs){
            #if DEBUG == 1
                //Serial.print("Executing Input Main Loop!");Serial.println(millis());
            #endif
            lastMillis = millis();

            internalLoop(dt);

        }

    }


    void internalLoop(unsigned long deltaTime){
    
        // Rotary Inputs
        inputOutData.rotaryCounter = getRotaryCounter();
        inputOutData.rotarySwitch  = getRotaryPushState();
        
        // Analog inputs
        uint16_t rawAnalogRead = analogRead(INPUT_VOLTAGE_SENSE_PIN);

        inputOutData.voltageSense = rawAnalogRead * 5.0f / 1023.0f * 100.0f;

        // Switch Inputs
        inputOutData.switchOk = digitalRead(INPUT_BUTTON_OK_PIN);
        inputOutData.switchBack = digitalRead(INPUT_BUTTON_BACK_PIN);


        #if DEBUG == 1
            if(inputOutData.rotarySwitch == 1){
                Serial.print("Rotary Switch: ");Serial.println(inputOutData.rotarySwitch);
            }
            if (inputOutData.rotaryCounter != 0){
                Serial.print("Rotary Counter: ");Serial.println(inputOutData.rotaryCounter);
            }
        #endif

    }

};

