/*
  LCDdisplay.cpp - Library for display things.
  Created by Maxime MERKLEN, April 20 2021.
*/

#include "Arduino.h"
#include "LCDdisplay.h"
#include "LiquidCrystal.h"


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

LCDdisplay:: LCDdisplay()
{

}


//fonction afficher température
void  LCDdisplay::displayTemp(float t, float h){

    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temp :  ");
  lcd.setCursor(0,1);
  lcd.print("Hygro : ");
  lcd.setCursor(13,1);
  lcd.print("%");
    lcd.setCursor(7,0);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(t);
  lcd.setCursor(8 ,1);
  lcd.print(h);

  delay(5000);
  lcd.noDisplay();
  
}


//fonction afficher erreur
void  LCDdisplay::displayERROR(String error){
    lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(error);
  delay(5000);
  lcd.noDisplay();
}
