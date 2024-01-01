#ifndef __FSM_H__
#define __FSM_H__

#include <LiquidCrystal_I2C.h>

#include "taskInput/mainInput.h"

enum STATE{
    STATE_WELCOME = 0,
    STATE_CONSTANT_CURRENT ,
    STATE_CONSTANT_POWER,
    STATE_MPPT,
    STATE_END
};

struct __state{
    void (*process)(unsigned long) = nullptr;
    void (*screen)(LiquidCrystal_I2C) = nullptr;
    void (*endState)() = nullptr;
    STATE nextState = STATE_END;
};

extern struct __state states[STATE_END];
extern enum STATE fsmCurrentState;

extern struct taskInput::inputData lastInputData;

void fsmLoop(unsigned long deltaTime);
void fsmScreen(LiquidCrystal_I2C lcd);
void fsmNext();

#endif //__FSM_H__