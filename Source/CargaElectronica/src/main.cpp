#include <Arduino.h>
#include <Wire.h>
#include "taskInput/mainInput.h"
#include "taskDcLoad/mainDcLoad.h"
#include "taskScreen/mainScreen.h"



void setup() {

  Serial.begin(9600);

  taskInput::inputInitialize();
  taskDcLoad::dcLoadInitialize();
  taskScreen::screenInitialize();

}

long setPoint;


void loop() {

  taskInput::inputMainLoop();
  taskDcLoad::dcLoadMainLoop();
  taskScreen::screenMainLoop();

  
  
#if 0

  setPoint = map((float)statusData.supply, 0, 500, 0, 255);
  analogWrite(9, setPoint);

  //Serial.println(rotaryContador);
  gScreenData.voltage = statusData.supply/100.0f;
  gScreenData.current = setPoint;


  // Update screen 'Process'
  if(millis() > lastScreenMillis + SCREEN_PERIOD ){
    screenSetParams(gScreenData);
    lastScreenMillis = millis();
  }

  // Measure process
  if(millis() > lastMeasureMillis + MEASURES_PERIOD){

  }

  // Update status 'Process'
  if(millis() > lastStatusMillis + STATUS_PERIOD ){
    statusMainLoop();
    gScreenData.voltage = statusData.supply/10.0f;
    lastStatusMillis = millis();
  }

  delay(200);

#endif 

}