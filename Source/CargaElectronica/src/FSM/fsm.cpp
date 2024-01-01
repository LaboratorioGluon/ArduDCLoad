#include <FSM\fsm.h>

struct __state states[STATE_END];
enum STATE fsmCurrentState;
struct taskInput::inputData lastInputData;

void fsmLoop(unsigned long deltaTime){
    if(states[fsmCurrentState].process != nullptr){
        states[fsmCurrentState].process(deltaTime);
    }
}

void fsmScreen(LiquidCrystal_I2C lcd){
    
    if(states[fsmCurrentState].screen != nullptr){
        states[fsmCurrentState].screen(lcd);
    }
}

void fsmNext(){

    if(states[fsmCurrentState].endState != nullptr){
        states[fsmCurrentState].endState();
    }

    if (states[fsmCurrentState].nextState != STATE_END){
        fsmCurrentState = states[fsmCurrentState].nextState;
    }

}