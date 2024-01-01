#ifndef __FSM_CONSTANT_CURRENT_H__
#define __FSM_CONSTANT_CURRENT_H__

#include <FSM/fsm.h>

void fsmConstantCurrent_process(unsigned long deltaTime);

void fsmConstantCurrent_screen(LiquidCrystal_I2C lcd);

void fsmConstantCurrent_endState();

#endif //__FSM_CONSTANT_CURRENT_H__