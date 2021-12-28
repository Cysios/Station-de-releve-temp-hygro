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
//biblitohèque perso
#include "LCDdisplay.h"


#define DHTPIN 2 
#define DHTTYPE DHT22 

RTC_DS1307 rtc;
DHT dht(DHTPIN, DHTTYPE);
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const int chipSelect = 10;
unsigned int timeRead=10000;
LCDdisplay screen;
int pinBouton;
int clock_1=0,clock_2=0;
int buttonCheck=3000;
boolean etatBouton=HIGH;


void setup() {
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinBouton = 9;
  pinMode(pinBouton,INPUT_PULLUP);

  //Lancement du programme pour le capteur DHT
  dht.begin();
  if (! rtc.begin()) {
    //Serial.println("Couldn't find RTC");
    //Serial.flush();
    screen.displayERROR("RTC");
    abort();
  }
  //Contrôle que la carte SD est bien disponible pour enregistrement
  if (!SD.begin(chipSelect)) {
    //Serial.println("Card failed, or not present");
    // don't do anything more:
    screen.displayERROR("Card Failed");
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
  
  if(clock_1>=buttonCheck)//contrôle d'horlgoge du boutton pour afficher les valeurs mesurées
  {
      etatBouton = digitalRead(pinBouton);
      if (etatBouton==LOW)//test bouton
    {
      readSensors();
    }
    clock_1=0;
  }

  if(clock_2>=timeRead)//contrôle d'horloge d'enregistrement des valeurs mesurées
  {
    String dataString=readSensors(); // Récupère valeur des capteurs
    String timeString=readTime(); //Récupère horadatage
    Serial.println(dataString+timeString); //affiche au moniteur la relève du capteur et son horodatage
    File dataFile = SD.open("datalog.txt", FILE_WRITE); // Ouvre ou créé un fichier sur la carte SD disponible
    if (dataFile) { // Si pas d'erreur alors
      dataFile.println(dataString+timeString); // Ecrit dans le fichier la valeur de 
      //digitalWrite(GreenLED, HIGH);
      dataFile.close(); //  Ferme le fichier (requis, sinon il ne peut plus le réouvrir sur une autre session
      //digitalWrite(GreenLED, LOW);
    }
    else{
      screen.displayERROR("Erreur 1");
    }
    clock_2=0;


  }
delay(1000);
clock_1+=1000;
clock_2+=1000;
  
}

//Fonction retourne la valeur des capteurs (température et hygrométrie)
String readSensors(){
  //digitalWrite(YellowLED, HIGH);
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
    screen.displayERROR("Failed to read");
    return dataString;
  }
  
  dataString=String(h)+"%"+","+String(t)+"°C"+","; // concaténation des valeurs en string
  //digitalWrite(YellowLED, LOW);
  screen.displayTemp(t, h);
  return dataString;
}

//Fonction retourne la date FORMAT (JOUR/MOIS/ANNEE HH:MM:SS)
String readTime(){

  String timeString="";
  DateTime now = rtc.now();
  timeString=String(now.day())+"/"+String(now.month())+"/"+String(now.year())+" "+String(now.hour())+":"+String(now.minute())+":"+String(now.second());

  return timeString;  
}
