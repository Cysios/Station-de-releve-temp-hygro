//Prototype v0.7.0

// include the library code:
#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT22

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Temp :  ");
  lcd.setCursor(0,1);
  lcd.print("Hygro : ");
  lcd.setCursor(13,1);
  lcd.print("%");
  dht.begin();
}

void loop() {
  delay(2000);
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  lcd.setCursor(7,0);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(t);
  lcd.setCursor(8 ,1);
  lcd.print(h);
  
}
