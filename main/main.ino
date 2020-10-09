//Fonctions complémentaires: led de signalement lecture valeur capteur;
//led de signalement enregsitrement carte SD
//Affichage à chaque boot "nouvelle capture"


//bibliothèque horloge
#include "RTClib.h"
//bibliothèque Capteur de temp. et Hygro.
#include "DHT.h"
//bibliothèque carte SD
#include "SPI.h"
#include "SD.h"

#define DHTPIN 2 
#define DHTTYPE DHT22 

RTC_DS1307 rtc;
DHT dht(DHTPIN, DHTTYPE);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int chipSelect = 10;

void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  dht.begin();
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1);
  }

  //informe du lancement d'un nouvelle session d'enregistrement
  Serial.println("Nouvelle session d'enregistrement");
  
}

void loop() {
  
  delay(3000);
  readTime();
  String dataString=readSensors();
  Serial.println(dataString);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
  }
  
}


String readSensors(){
  String dataString="";
   // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    dataString="Failed to read from DHT sensor!";
    
    return dataString;
  }
  
  dataString=String(h)+"%"+","+String(t)+"°C"+",";

  return dataString;
}

void readTime(){

  DateTime now = rtc.now();
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.print(",");
  Serial.print("(");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(")");
  Serial.print(",");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(",");
}
