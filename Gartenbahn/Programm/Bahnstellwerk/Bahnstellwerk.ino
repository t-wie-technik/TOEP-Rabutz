#include "wifi.h"

IPAddress eitech01  (192,168,1,11);
IPAddress eitech02  (192,168,1,12);
IPAddress eitech03  (192,168,1,13);
IPAddress eitech04  (192,168,1,14);
IPAddress eitech05  (192,168,1,15);
IPAddress eitech06  (192,168,1,16);
IPAddress eitech07  (192,168,1,17);
IPAddress eitech08  (192,168,1,18);
IPAddress eitech09  (192,168,1,19);

char* fahrbefelName[]   = {"/V36-left","/V36-STOP","/V36-right" ,"/1"  ,"/2"  ,"/3"   };
bool  tasterAlt[]       = {HIGH       ,HIGH       ,HIGH        ,HIGH         ,HIGH         ,HIGH          };
int   fahrbefelInput[]  = {15         ,25         ,18          ,19           ,20           ,21            };
IPAddress  bahnIp[]     = {eitech09   ,eitech09   ,eitech09    ,eitech09 ,eitech09     ,eitech09      };

int frequenzPin         = 37;
int frequenz            = 200; //Hz

void setup() {
  Serial.begin(9600);
  // while (!Serial); // rausnehmen!
    
  //PINMODE
    pinMode(frequenzPin, OUTPUT);
      
  //WIFI
    Serial.println("setup");
    SetupWiFi();
      
  //TASTER
    for (int i = 0; i < 6; i++) {
      pinMode(fahrbefelInput[i], INPUT);
    }
      
  //Frequenz
    //tone(frequenzPin,frequenz);
}

void loop() {
  //WIFI
    UpdateWiFiHandler();
  
  //TASTER
    for (int i = 0; i < 6; i++) {
      bool taster(digitalRead(fahrbefelInput[i]));
      if (taster == LOW && tasterAlt[i] == HIGH) {
        //wifi Ausgab
         //SendRequestToOther("/V36-left", eitech08);
     
         tastersent(bahnIp[i] , fahrbefelName[i]);
      }
      tasterAlt[i] = taster;
    }
}


void tastersent(IPAddress empfanger, char* message){
  SendRequestToOther(message, empfanger);
}

void Commands(String first,String second, String third, String forth, String fith){
  if (first == "debug"){
    //Serial.println("start");
    //SendRequestToOther("/V36-left",V36);
  }
}
