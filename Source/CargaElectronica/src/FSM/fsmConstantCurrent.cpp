#include <FSM/fsmConstantCurrent.h>

#include <Arduino.h>

#include "taskInput/mainInput.h"
#include "calibration.h"
#include "globalConfig.h"


char templateShowValues[2][17] ={ " Const.DC      ", "V:     I:     mA"};

uint16_t targetCurrent = 100; //[mA]
uint16_t targetVoltage = 0;
uint16_t multiplier = 1;

uint8_t first_run = 1;

uint8_t isOn = 0;

long setPoint = 0;
float resistorFactor = 0.0f;

void fsmConstantCurrent_process(unsigned long deltaTime){

    if(taskInput::inputOutData.rotarySwitch == 1 && 
        lastInputData.rotarySwitch == 0){

        multiplier *= 10;
        if (multiplier > 1000){
            multiplier = 1;
        }
    }
    if (taskInput::inputOutData.switchOk == 1 &&
        lastInputData.switchOk == 0){
        isOn = isOn?0:1;
    }

    if (taskInput::inputOutData.switchBack == 1 &&
        lastInputData.switchBack == 0){
        fsmNext();
    }
    
    targetCurrent += taskInput::inputOutData.rotaryCounter*multiplier;

    if(targetCurrent > OUTPUT_MAX_CURRENT_MA){
        targetCurrent = OUTPUT_MAX_CURRENT_MA;
    }

    targetVoltage = targetCurrent * CALIBRATION_MAIN_RESISTOR_VALUE / 10.0f; // 10.0f to move from mV to 10mV

    if(isOn){
        
        if(targetVoltage > CALIBRATION_MAX_VOLTAGE10MV){
            targetVoltage = CALIBRATION_MAX_VOLTAGE10MV;
        }

        setPoint = map((float)targetVoltage, 0, 500, 0, 255);
        Serial.println("Setting point: " + String(setPoint));
        analogWrite(9, setPoint);

    }else{

        analogWrite(9,0);
        
    }

    lastInputData = taskInput::inputOutData;

}

void fsmConstantCurrent_screen(LiquidCrystal_I2C lcd){

    if(first_run){
        lcd.setCursor(0,0);
        lcd.print(templateShowValues[0]);
    }

    if (isOn){
        lcd.setCursor( 11,0);
        float power = (taskInput::inputOutData.voltageSense / V_TO_100MV) * (targetCurrent / 1000.0f);
        if (power >= 10.0f){
            lcd.print(power, 1);
        }else{
            lcd.print(power, 2);
        }
        lcd.setCursor(15,0);
        lcd.print("W");

        if(power > 15.0f){
            digitalWrite(DCLOAD_FAN_OUTPUT_PIN, HIGH);
        }
    }
    
    // Repintamos segunda linea
    lcd.setCursor(0,1);
    lcd.print(templateShowValues[1]);

    // Marcamos si la fuente está activa o no
    lcd.setCursor(0,0);
    if(isOn){   
        lcd.print('X');
    }else{
        lcd.print(' ');
    }

    
    uint8_t lenStringCurrent = (uint8_t)(floor(log10f(targetCurrent)));

    lcd.setCursor(2,1);
    if (taskInput::inputOutData.voltageSense > 1000){
        lcd.print((float)(taskInput::inputOutData.voltageSense/100.0f), 1);
    }else{
        lcd.print((float)(taskInput::inputOutData.voltageSense/100.0f), 2);
    }
    
    lcd.setCursor(9+3-lenStringCurrent,1);
    lcd.print(targetCurrent);
    lcd.cursor();
    lcd.setCursor(9 + 3 - (uint8_t)(floor(log10f(multiplier))) , 1);

    first_run = 0;

}

void fsmConstantCurrent_endState(){
    if(isOn){
        analogWrite(9,0);
        isOn = false;
    }
    first_run = 1;
}