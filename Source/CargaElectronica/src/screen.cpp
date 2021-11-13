
#include "screen.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "screen.h"

LiquidCrystal_I2C lcd(0x27,16,2);

void configureScreen(){

  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("DC Load");
  lcd.setCursor(0,1);
  lcd.print("V:     I:     mA");

}


void screenSetParams(struct screenData pData){

  lcd.setCursor(2,1);
  lcd.print(pData.voltage);

  lcd.setCursor(9,1);
  lcd.print(pData.current);

}