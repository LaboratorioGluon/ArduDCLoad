#include "status.h"
#include <Arduino.h>

#define STATUS_SUPPLY_PIN A0

struct __statusData statusData;


#define ADC_REPES 10
uint32_t adcValue;
uint8_t i;


void statusMainLoop(){
    //Read ADC values from the Potentiometer
    adcValue = 0;
    for( i = 0; i < ADC_REPES; i++){
      adcValue += analogRead(A0);
    }
    
    adcValue = (uint32_t) (adcValue/ADC_REPES *5.0f /1024.0f * 100.0f) ;
    statusData.supply = adcValue;
}