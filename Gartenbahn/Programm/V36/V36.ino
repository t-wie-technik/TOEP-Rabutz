#include "wifi.h"
#include "music.h"

//DEBUG (Serielermonitor)
  /*0 = off
    1 = all on
    2 = Motordriver
    3 = Sensoren
    4 = light/dir
    5 = driveaction
  */
  #define debug 0
//PIN Mode
  //Input 
  //J1=15 J2=25 J3=18 J4=19 J5=20 J6=21 J7=16
  #define dipSwitchPin A0  //Start Position
  // Rechts schneller  Links langsamer
  #define slowFrontPin 16  //Sensor Front Links
  #define fastFrontPin 21  //Sensor Front Rechts
  #define slowBackPin 20   //Sensor Back  Links
  #define fastBackPin 19   //Sensor Back  Rechts
  //HIGH = nicht gedrückt / LOW = gedrückt

#define freq 400
#define freq_min 300
#define freq_max 500
#define zeit 200
#define tast_1 20
#define tast_2 21
bool tast_1_alt = HIGH;
bool tast_2_alt = HIGH;

  //Output
  //(S1 = 37) (M1 = 7/6) (M2 = 1/0) (M3 = 3/2) (M4 = 5/4) (Schwarzes Kabel nach Stominput)
  #define speakerPin 37   //S1 =  Lautsprcher
  #define lightPin0 7     //M1 =  Licht
  #define lightPin1 6
  #define motorDirPin 13   // =  Motor Richtung
  #define motorSpedPin 18  // =  Motor Geschwindigkeit

                          //J1,J2,J4,J5,J6,J7 
  int   pinInput[]        = {15,25,19,20,21,16};
                          //S1,M1, M2, M3, M4, J3
  int   pinOutput[]       = {37,7,6,1,0,3,2,5,4,18};
//<PinMode

//Variablen
#define spedFast 250 //Schnelle Geschwindigkeit
#define spedSlow 100  //Langsame Geschwindigkeit
#define spedAdd 40   //Geschwindigskeitzunahme 1 = Schnell 100 = Langsamm
#define spedSubt 20  //Geschwindigkeitsabnahme 1 = Schnell 100 = Langsamm
int driveAction = 0; //Fahrbefehl |0    |1       |2      |3       |4         |5         |6
                                //|STOP |Starten |Stopen |Langsam |Schneller |Langsamer |Schnell
int driveDir = 1;        //Fahrtrichtung (0=Richtung Rennstrecke) (1=Richtung Pumpkraftwerk)
int driveStorage;    //Fahrtenspeicher |0       |1          |2        |3          |4        |5          |6 
                                     //|Garten  |Verbinder  |Bahnhof  |Verbinder  |Bahnwerk |Verbinder  |Rennstrecke
int dip;

void setup() {
// Serial
  Serial.begin(9600);

  //WIFI
  SetupWiFi();

  //PINMODE
  for (int i = 0; i < 6; i++) {
    pinMode(pinInput[i], INPUT);
  }
  for (int i = 0; i < 10; i++) {
    pinMode(pinOutput[i], OUTPUT);
  }
  pinMode(motorDirPin, OUTPUT);
  //Position
  dipSwitchRead();
}

void loop() {
//WIFI
  UpdateWiFiHandler();
  
//Fahren
  switch (driveAction) {
    case 0:
      stop();
    break;
    case 1:
      starting();
    break;
    case 2:
      stoping();
    break;
    case 3:
      slow();
    break;
    case 4:
      faster();
    break;
    case 5:
      slower();
    break;
    case 6:
      fast();
    break;
  }

//Fahrtenspeicher Begrenzer
  if (driveStorage < 0) {
    driveStorage = 0;
  }else if (driveStorage > 6){
    driveStorage = 6;
  }

//Fahrtenactionen Begrenzer
  if (driveAction < 0) {
    driveAction = 0;
  }else if (driveAction > 6){
    driveAction = 6;
  }
}

void driveStorageWriter(){
  switch (driveDir){
    case 0:
      driveStorage = driveStorage - 1;
    break;
    case 1:
      driveStorage = driveStorage + 1;
    break;
  }
}

void start (bool dir){
  if (driveAction == 0){
    driveDir = dir;
    driveAction = 1;
  }
}

void motorDriver (int sped){
  switch (driveDir){
    case 0:
      digitalWrite(motorDirPin, LOW);
    break;
    case 1:
      digitalWrite(motorDirPin, HIGH);
    break;
  }
  analogWrite(motorSpedPin,sped);
}

void dipSwitchRead (){
  dip = analogRead(dipSwitchPin);
  if (dip > 1020){
    driveStorage = 4;
  }else if (dip > 880 && dip < 900){
    driveStorage = 0;
  }else if (dip > 455 && dip < 475){
    driveStorage = 2;
  }else if (dip > 124 && dip < 135){
    driveStorage = 6;
  }
}

void lightControll(){
  switch (driveDir){
    case 0:
      digitalWrite(lightPin0, HIGH);
      digitalWrite(lightPin1, LOW);
    break;
    case 1:
      digitalWrite(lightPin0, LOW);
      digitalWrite(lightPin1, HIGH);
    break;
  }
}

//Driving
void stop (){
    motorDriver(0);
}

void starting (){
    lightControll();
    musicStart(speakerPin);
    for (int i = 0; i < spedSlow; i++){
        motorDriver(i);
        delay(spedAdd);
    }
    driveAction = driveAction + 2;
}

void stoping(){
    for (int i = spedSlow; i > 0; i--){
        motorDriver(i);
        delay(spedSubt);
    }
    musicStop(speakerPin);
    driveAction = driveAction - 2;
}

void slow(){
    motorDriver(spedSlow);
    readSensorSlow();
    readSensorFast();
}

void faster (){
    for (int i = spedSlow; i < spedFast; i++){
        motorDriver(i);
        delay(spedAdd);
    }
    driveStorageWriter();
    driveAction = driveAction + 2;
}

void slower (){
    for (int i = spedFast; i > spedSlow; i--){
        motorDriver(i);
        delay(spedSubt);
    }
    driveStorageWriter();
    driveAction = driveAction - 2;
}

void fast (){
    motorDriver(spedFast);
    readSensorSlow();
}

//Sensoren
void readSensorSlow(){
    switch (driveDir){
        case 0:
            if (readSensor(slowFrontPin) = true){
                driveAction - 1;
                
            
        break;
        case 1:
            if (readSensor(slowBackPin) = true){
                driveAction - 1;
                
            }
        break;
    }
}

void readSensorFast(){
    switch (driveDir){
        case 0:
            if (readSensor(fastFrontPin) = true){
                driveAction + 1;
                
            }
        break;
        case 1:
            if (readSensor(fastBackPin) = true){
                driveAction + 1;
                
            }
        break;
    }
}

///Frequenzmesser
bool readSensor (int pin){
    float freq_in = (float)1000/( (float)pulseIn(pin, HIGH,5000) / (float)500);
    if (freq_in < freq_max && freq_in > freq_min){
        return true;
    }else {
        return false;
    }
}


//WIFI
IPAddress eitech01(192,168,1,11);
IPAddress eitech02(192,168,1,12);
IPAddress eitech03(192,168,1,13);
IPAddress eitech04(192,168,1,14);
IPAddress eitech05(192,168,1,15);
IPAddress eitech06(192,168,1,16);
IPAddress eitech07(192,168,1,17);
IPAddress eitech08(192,168,1,18);


void Commands(String first,String second, String third, String forth, String fith){
  if (first == "faster"){
    driveAction = driveAction + 1;
  }
  if (first == "slower"){
    driveAction = driveAction - 1;
  }
  if (first == "stop"){
    driveAction = 0;
  }
  if (first == "start-pumpkraft"){
    start(1);
  }
  if (first == "start-rennstrecke"){
    start(0);
  }
}

