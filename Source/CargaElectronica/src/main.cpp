#include <Arduino.h>
#include <Wire.h>
#include "rotary.h"
#include "screen.h"
#include "status.h"

#define SCREEN_PERIOD 100
#define MEASURES_PERIOD 100
#define STATUS_PERIOD 25

struct screenData gScreenData;


unsigned long lastMillis;
unsigned long lastScreenMillis;
unsigned long lastMeasureMillis;
unsigned long lastStatusMillis;


void setup() {
  rotaryConfigure();
  Serial.begin(9600);

  pinMode(9,155);
  TCCR1B = (TCCR1B & B11111000) | B00000010; // for PWM frequency of 31372.55 Hz

  rotaryConfigure();
  configureScreen();

  gScreenData.voltage = 0;
  gScreenData.current = 0;

  lastMillis = millis();
  lastScreenMillis = millis();
  lastMeasureMillis = millis();
  lastStatusMillis = millis();
}

long setPoint;


void loop() {

  
  
  
  setPoint = map((float)statusData.supply, 0, 500, 0, 255);
  analogWrite(9, setPoint);

  Serial.println(rotaryContador);
  gScreenData.voltage = statusData.supply/100.0f;
  gScreenData.current = setPoint;


  // Update screen 'Process'
  if(millis() > lastScreenMillis + SCREEN_PERIOD ){
    screenSetParams(gScreenData);
    lastScreenMillis = millis();
  }

  // Update screen 'Process'
  if(millis() > lastMeasureMillis + MEASURES_PERIOD){

  }

  // Update status 'Process'
  if(millis() > lastStatusMillis + STATUS_PERIOD ){
    statusMainLoop();
    gScreenData.voltage = statusData.supply/10.0f;
    lastStatusMillis = millis();
  }

  delay(200);

}