#ifndef __FSM_MPPT_H__
#define __FSM_MPPT_H__

#include <FSM/fsm.h>

void fsmMppt_process(unsigned long deltaTime);

void fsmMppt_screen(LiquidCrystal_I2C lcd);


#endif //__FSM_MPPT_H__