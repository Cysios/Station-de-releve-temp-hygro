//Programme de station de releve arduino pour temperature et hygrometrie
//Auteur: Maxime MERKLEN


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
  //Lancement du programme pour le capteur DHT
  dht.begin();
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  //Contrôle que la carte SD est bien disponible pour enregistrement
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
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
  
  delay(60000);
  readTime();
  String dataString=readSensors();
  String timeString=readTime();
  Serial.println(dataString+timeString);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString+timeString);
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

String readTime(){

  String timeString="";
  DateTime now = rtc.now();
  timeString=String(now.day())+"/"+String(now.month())+"/"+String(now.year())+" "+String(now.hour())+":"+String(now.minute())+":"+String(now.second());

  return timeString;  
}
