#include "wifi.h"
void setup(){
  SetupWiFi();
  Serial.begin(9600);
  pinMode(37,OUTPUT);
}
void loop(){
  UpdateWiFiHandler();
  
    
  
}
IPAddress V36(192,168,1,70);
IPAddress Bahnhof (192,168,1,34);

void tastersent(){
    SendRequestToOther("/V36-left", V36);
}

void Commands(String first,String second, String third, String forth, String fith){
  if (first == "V36-left"){
    tone(37,200);
    delay(10);
    noTone(37);
 }
 if (first == "V36-STOP"){
    tone(37,300);
    delay(10);
    noTone(37);
 }
 if (first == "V36-right"){
    tone(37,400);
    delay(10);
    noTone(37);
 }
 if (first == "1"){
    tone(37,500);
    delay(10);
    noTone(37);
 }
 if (first == "2"){
    tone(37,600);
    delay(10);
    noTone(37);
 }
 if (first == "3"){
    tone(37,700);
    delay(10);
    noTone(37);
 }
}
