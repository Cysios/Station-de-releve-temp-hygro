# projet-Station-de-releve-temp-hygro

## Résumé

Projet pour Arduino UNO dont la finalité est de mesurer:
* la température et l'hygrométrie
* de manière autonome : Sauvegarde les données sur une carte SD (csv)
* sur une durée de temps de 1 mois minimum(dépend le capacité de stockage)

### Contexte 
Mesurer ces grandeurs dans une cave pour vérifier les conditions de conservation du vin qui y est stocké.
Dans une cave il est difficilement possible de transmettre des données sur un serveur de stockage des données (réseau indisponible WIFI ou 3G)
Le système Arduino permet de répondre à ces besoins avec un coup limité et une fiabilité correct pour un usage de particulier.

## Prérequis

### Composants
* Arduino UNO  
* DHT 22(code configuré par défaut pour DHT22) ou DHT11 https://learn.adafruit.com/dht/overview  
* Velleman VMA202 : ARDUINO®COMPATIBLE DATA LOGGING SHIELD  https://www.velleman.eu/products/view/?id=435508
* 3 LEDS: Rouge,Jaune,Verte  
* Résistances: 3x220 ohm; 1x10K ohm
* Carte SD (8Go)

### Codes

Initialiser l'heure sur le composant RTC avec l'aide d'un code exemple RTClib: ds1307.ino

## Fonctions

* Toutes les X secondes:
  * Mesurer température(°C) et hygrométrie(%)
  * Enregistrer les mesures:
    * sur la carte SD au format CSV
    * horodatée avec JJ/MOIS/ANNEE HEURE:MIN:SEC

* Enregistrer sur la carte SD l'information en cas de nouvelle session(coupure de courant, reset de l'Arduino)

### Dépendances
//bibliothèque horloge  
RTClib.h  
//bibliothèque Capteur de temp. et Hygro.  
DHT.h  
//bibliothèque carte SD  
SPI.h  
SD.h  

# License
[CeCILL v2.1](https://cecill.info/licences.fr.html)
