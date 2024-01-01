
#include <FSM/fsmWelcome.h>

#include "taskInput/mainInput.h"

char templatesWelcome[2][17] ={ "    Welcome!!   ", "   ArduDCLoad   "};

void fsmWelcome_process(unsigned long deltaTime){
    if(taskInput::inputOutData.rotarySwitch == 1 &&
        lastInputData.rotarySwitch == 0){
        fsmCurrentState = STATE_CONSTANT_CURRENT;
    }

    lastInputData = taskInput::inputOutData;
}

void fsmWelcome_screen(LiquidCrystal_I2C lcd){
    lcd.setCursor(0,0);
    lcd.print(templatesWelcome[0]);
    lcd.setCursor(0,1);
    lcd.print(templatesWelcome[1]);
}