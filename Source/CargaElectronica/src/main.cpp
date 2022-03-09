#include <Arduino.h>
#include <Wire.h>
#include "taskInput/mainInput.h"
#include "taskDcLoad/mainDcLoad.h"
#include "taskScreen/mainScreen.h"

#include "FSM/fsm.h"

#include "FSM/fsmConstantCurrent.h"
#include "FSM/fsmWelcome.h"
#include "FSM/fsmMppt.h"

/*
#include <RotaryEncoder.h>
extern RotaryEncoder encoder;
*/

void setup() {


  Serial.begin(9600);

  taskInput::inputInitialize();
  taskDcLoad::dcLoadInitialize();
  taskScreen::screenInitialize();

  states[STATE_WELCOME].process = fsmWelcome_process;
  states[STATE_WELCOME].screen = fsmWelcome_screen;
  states[STATE_WELCOME].nextState = STATE_CONSTANT_CURRENT;

  states[STATE_CONSTANT_CURRENT].process = fsmConstantCurrent_process;
  states[STATE_CONSTANT_CURRENT].screen = fsmConstantCurrent_screen;
  states[STATE_CONSTANT_CURRENT].endState= fsmConstantCurrent_endState;
  states[STATE_CONSTANT_CURRENT].nextState = STATE_MPPT;

  states[STATE_MPPT].process = fsmMppt_process;
  states[STATE_MPPT].screen = fsmMppt_screen;
  states[STATE_MPPT].nextState = STATE_CONSTANT_CURRENT;


  fsmCurrentState = STATE_WELCOME;

}

void loop()
{
    
    taskInput::inputMainLoop();
    taskDcLoad::dcLoadMainLoop();
    taskScreen::screenMainLoop();

}