//Programme de station de releve arduino pour temperature et hygrometrie 
// v0.7.0
//Auteur: Maxime MERKLEN


//bibliothèque horloge
#include "RTClib.h"
//bibliothèque Capteur de temp. et Hygro.
#include "DHT.h"
//bibliothèque carte SD
#include "SPI.h"
#include "SD.h"
//bibliothèque écran LCD
#include <LiquidCrystal.h>

#define DHTPIN 2 
#define DHTTYPE DHT22 

RTC_DS1307 rtc;
DHT dht(DHTPIN, DHTTYPE);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int chipSelect = 10;
int RedLED=5;
int GreenLED=6;
int YellowLED=7;
unsigned int timeRead=3000;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 0, en = 1, d4 = 8, d5 = 9, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //Intialisation sortie digital pour LEDs d'affcichage
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(YellowLED, OUTPUT);

  //Lancement du programme pour le capteur DHT
  dht.begin();
  if (! rtc.begin()) {
    //Serial.println("Couldn't find RTC");
    //Serial.flush();
      digitalWrite(RedLED, HIGH);
    abort();
  }
  //Contrôle que la carte SD est bien disponible pour enregistrement
  if (!SD.begin(chipSelect)) {
    //Serial.println("Card failed, or not present");
    // don't do anything more:
      digitalWrite(RedLED, HIGH);
    while (1);
  }
  //informe du lancement d'une nouvelle session d'enregistrement
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println("Nouvelle session d'enregistrement");
    dataFile.close();
  }

  
  
}

void loop() {
  
  delay(timeRead); //Fréquence de relève de la température et hygrométrie
  String dataString=readSensors(); // Récupère valeur des capteurs
  String timeString=readTime(); //Récupère horadatage
  Serial.println(dataString+timeString); //affiche au moniteur la relève du capteur et son horodatage
  File dataFile = SD.open("datalog.txt", FILE_WRITE); // Ouvre ou créé un fichier sur la carte SD disponible
  if (dataFile) { // Si pas d'erreur alors
    dataFile.println(dataString+timeString); // Ecrit dans le fichier la valeur de 
    digitalWrite(GreenLED, HIGH);
    dataFile.close(); //  Ferme le fichier (requis, sinon il ne peut plus le réouvrir sur une autre session
    digitalWrite(GreenLED, LOW);
  }
  else{
    digitalWrite(RedLED, HIGH);
  }
  
}

//Fonction retourne la valeur des capteurs (température et hygrométrie)
String readSensors(){
  digitalWrite(YellowLED, HIGH);
  String dataString="";
   // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  // float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) { // Check if you need || isnan(f)
    dataString="Failed to read from DHT sensor!";
    digitalWrite(RedLED, HIGH);//informe visuellement en cas d'erreur
    return dataString;
  }
  else {
    digitalWrite(RedLED,LOW);
  }
  
  dataString=String(h)+"%"+","+String(t)+"°C"+","; // concaténation des valeurs en string
  digitalWrite(YellowLED, LOW);
  //displayTemp(t, h);
  return dataString;
}

//Fonction retourne la date FORMAT (JOUR/MOIS/ANNEE HH:MM:SS)
String readTime(){

  String timeString="";
  DateTime now = rtc.now();
  timeString=String(now.day())+"/"+String(now.month())+"/"+String(now.year())+" "+String(now.hour())+":"+String(now.minute())+":"+String(now.second());

  return timeString;  
}

//fonction afficher température
void displayTemp(float t, float h){

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
