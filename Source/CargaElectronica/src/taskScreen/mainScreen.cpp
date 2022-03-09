#include "taskScreen/mainScreen.h"
#include "taskScreen/screenTemplates.h"

#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <stdint.h>

#include "taskInput/mainInput.h"

#include "FSM/fsm.h"

constexpr unsigned long ScreenPeriodMs = 300; // 100ms 

namespace taskScreen {

    struct screenData screenOutData;

    enum screenState {
        SCREEN_WELCOME = 0,
        SCREEN_SHOW_DATA,
        SCREEN_NULL
    };

    enum screenState currentScreenState;
    enum screenState previousScreenState = SCREEN_NULL;

    taskInput::inputData lastInputData;


    LiquidCrystal_I2C lcd(0x27,16,2);

    unsigned long lastMillis;
    unsigned long dt;


    // Internal Functions
    void updateScreen();
    void setScreen(char t[2][17]);
    void internalLoop(unsigned long deltaTime);


    void screenInitialize(){
        currentScreenState = SCREEN_WELCOME;
        lcd.init(); 

        lcd.backlight();
        //setScreen(templatesWelcome);

    }

    

    void screenMainLoop(){

        // Calculate the time since the last call
        dt = millis() - lastMillis;

        if(dt > ScreenPeriodMs){
            #if DEBUG == 1
                //Serial.print("Executing Input Main Loop!");Serial.println(millis());
            #endif
            lastMillis = millis();

            internalLoop(dt);

        }

    }

    void setScreen(char t[2][17]){
            
            lcd.setCursor(0,0);
            lcd.print(t[0]);
            lcd.setCursor(0,1);
            lcd.print(t[1]);
    
    }



    void internalLoop(unsigned long deltaTime){
        fsmScreen(lcd);

#if 0
        if( currentScreenState == SCREEN_WELCOME && 
            taskInput::inputOutData.rotarySwitch == 1 &&
            lastInputData.rotarySwitch == 0){

                currentScreenState = SCREEN_SHOW_DATA;
        }

        updateScreen();

        if (currentScreenState == SCREEN_SHOW_DATA){
            
            char voltage[2];
            char decimals[3];
            char decimals2[3];
            itoa(taskInput::inputOutData.voltageSense/100,voltage,10);
            itoa(taskInput::inputOutData.voltageSense%100,decimals,10);
            
            if (strlen(decimals) == 1){
                decimals2[0] = '0';
                decimals2[1] = decimals[0];
                decimals2[2] = '\0';
            }else{
                decimals2[0] = decimals[0];
                decimals2[1] = decimals[1];
                decimals2[2] = '\0';
            }

            lcd.setCursor(2,1);
            lcd.print(voltage);
            lcd.setCursor(3,1);
            lcd.print('.');
            lcd.setCursor(4,1);
            lcd.print(decimals2);
        }

    
        lastInputData = taskInput::inputOutData;
#endif
    }


    void updateScreen(){
/*
        if(currentScreenState != previousScreenState){
            switch(currentScreenState){
                case SCREEN_WELCOME:
                    setScreen(templatesWelcome);
                    break;
                case SCREEN_SHOW_DATA:
                    setScreen(templateShowValues);
                    break;
            }
            previousScreenState = currentScreenState;
        }
*/
    }

}