
#include <FSM/fsmWelcome.h>

#include "taskInput/mainInput.h"

char templatesMppt[2][17] ={ " MPPT           ", "   ArduDCLoad   "};

void fsmMppt_process(unsigned long deltaTime){
    if (taskInput::inputOutData.switchBack == 1 &&
        lastInputData.switchBack == 0){
        fsmNext();
    }

    lastInputData = taskInput::inputOutData;
}

void fsmMppt_screen(LiquidCrystal_I2C lcd){
    lcd.setCursor(0,0);
    lcd.print(templatesMppt[0]);
    lcd.setCursor(0,1);
    lcd.print(templatesMppt[1]);
}