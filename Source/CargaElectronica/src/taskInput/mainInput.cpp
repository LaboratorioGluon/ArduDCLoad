#include <Arduino.h>

#include "taskInput/mainInput.h"
#include "taskInput/rotary.h"

#include "calibration.h"
#include "globalConfig.h"


constexpr unsigned long InputPeriodMs = 0; // 100ms 



namespace taskInput {

    unsigned long lastMillis;
    unsigned long dt;


    struct inputData inputOutData;
    
    void inputInitialize(){
        
        pinMode(INPUT_BUTTON_OK_PIN  , INPUT_PULLUP);
        pinMode(INPUT_BUTTON_BACK_PIN, INPUT_PULLUP);

        pinMode(INPUT_VOLTAGE_SENSE_PIN, INPUT);
        analogReference(EXTERNAL);
        
        rotaryConfigure();

    }


    void internalLoop(unsigned long deltaTime);

    void inputMainLoop(){

        rotaryTick();


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
        uint32_t rawAnalogRead= 0;
        uint16_t unitraw = 0;
        for( uint8_t i = 0; i < INPUT_ADC_REPEATS; i++){
            unitraw = analogRead(INPUT_VOLTAGE_SENSE_PIN);
            rawAnalogRead += unitraw;
            //rawAnalogRead += analogRead(INPUT_VOLTAGE_SENSE_PIN);
            
        }
        
        
        inputOutData.voltageSense = rawAnalogRead * CALIBRATION_ANALOG_REF / 1023.0f * V_TO_100MV * CALIBRATION_SENSE_FACTOR / INPUT_ADC_REPEATS;

        //Serial.println("Raw Analog Read: " + String(inputOutData.voltageSense));

        // Switch Inputs
        inputOutData.switchOk = digitalRead(INPUT_BUTTON_OK_PIN);
        inputOutData.switchBack = digitalRead(INPUT_BUTTON_BACK_PIN);


        #if DEBUG == 1
            if(inputOutData.rotarySwitch == 1){
                Serial.print("Rotary Switch: ");Serial.println(inputOutData.rotarySwitch);
            }
            if (inputOutData.rotaryCounter != 0){
                Serial.print("Rotary Counter: ");Serial.println((int32_t)inputOutData.rotaryCounter);
            }
        #endif

    }

};

