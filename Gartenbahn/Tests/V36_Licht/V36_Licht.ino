#include "wifi.h"
#include "musik.h"
int dir = 0;
void setup(){
  //SetupWiFi();
  Serial.begin(9600);
  pinMode(37,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}
void loop(){
  //UpdateWiFiHandler();
  tone(37,400);
    delay(50);
    noTone(37);
    delay(100);
    tone(37,400);
    delay(50);
    noTone(37);



    delay(10000);
    
  switch(dir){
    case 1:
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    break;
    
    case 0:
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
    break;
    
    case 2:
    digitalWrite(7,LOW);
    digitalWrite(6,HIGH);
    break;  
  }
  
}
IPAddress V36(192,168,1,70);
IPAddress Bahnhof (192,168,1,34);

void tastersent(){
    SendRequestToOther("/V36-left", V36);
}

void Commands(String first,String second, String third, String forth, String fith){
  if (first == "V36-left"){
    dir = 1;
    tone(37,200);
    delay(10);
    noTone(37);
 }
 if (first == "V36-STOP"){
    dir = 0;
    tone(37,400);
    delay(50);
    noTone(37);
    delay(100);
    tone(37,400);
    delay(50);
    noTone(37);
    
   
 }
 if (first == "V36-right"){
    dir = 2;
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
