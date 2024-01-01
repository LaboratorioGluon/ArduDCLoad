#ifndef __FSM_WELCOME_H__
#define __FSM_WELCOME_H__

#include <FSM/fsm.h>

void fsmWelcome_process(unsigned long deltaTime);

void fsmWelcome_screen(LiquidCrystal_I2C lcd);

#endif //__FSM_WELCOME_H__
