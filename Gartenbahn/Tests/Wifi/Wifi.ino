#include "wifi.h"
IPAddress V36  (192,168,1,11);
IPAddress Bahnhof (192,168,1,34);

void setup(){
  SetupWiFi();
  Serial.begin(9600);
  pinMode(37,OUTPUT);
  pinMode(15,INPUT);
}
void loop(){
  UpdateWiFiHandler();
if   (digitalRead(15)==LOW){
    Serial.println("sendSTART");
    SendRequestToOther("/V36-left", V36);
    Serial.println("sendEND");
  }
}

void tastersent(){
    
}

void Commands(String first,String second, String third, String forth, String fith){
  if (first == "debug"){
    Serial.println("start");
    SendRequestToOther("/V36-left", V36);
   
 }
}
