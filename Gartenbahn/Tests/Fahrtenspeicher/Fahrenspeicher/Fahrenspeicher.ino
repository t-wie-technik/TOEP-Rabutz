#include "music.h"

#define zeit 200
#define tast_1 20
#define tast_2 21
#define speaker_pin 37
bool tast_1_alt = HIGH;
bool tast_2_alt = HIGH;
int fahrtenspeicher =1;

void setup() {

  Serial.begin(9600);
  pinMode(tast_1, INPUT);
  pinMode(tast_2, INPUT);
}

void loop() {
  if (digitalRead(tast_1) == LOW && tast_1_alt == HIGH){
    fahrtenschreiber('g');
    musicStart(speaker_pin);
    tast_1_alt = LOW;
  }else if (digitalRead(tast_1) == HIGH && tast_1_alt == LOW){
    tast_1_alt = HIGH;
  }

  if (digitalRead(tast_2) == LOW && tast_2_alt == HIGH){
    fahrtenschreiber('r');
    musicStop(speaker_pin);
    tast_2_alt = LOW;
  }else if (digitalRead(tast_2) == HIGH && tast_2_alt == LOW){
    tast_2_alt = HIGH;
  }
  if (fahrtenspeicher < 0) {
    fahrtenspeicher = 0;
  }else if (fahrtenspeicher > 6){
    fahrtenspeicher = 6;
  }


}

/*Fahrtenspeicher
0 G     |1 GH       |2 H      |3 HW       |4 W      |5 WR       |6 R
Garten  |Verbinder  |Bahnhof  |Verbinder  |Bahnwerk |Verbinder  |Rennstrecke*/

void fahrtenschreiber(char dir){

  switch (dir){
    case 'g':
      fahrtenspeicher = fahrtenspeicher - 1;
    break;
    case 'r':
      fahrtenspeicher = fahrtenspeicher + 1;
    break;
  }
}
