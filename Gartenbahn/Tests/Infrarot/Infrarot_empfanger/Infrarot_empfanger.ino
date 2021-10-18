#define hintenLinks 19
#define hintenRechts 20
#define vorneLinks 21
#define vorneRechts 16
#define status 0

int   pinInput[]        = {15,25,19,20,21,16};

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

for (int i = 0; i < 6; i++) {
    pinMode(pinInput[i], INPUT);
  }


}

void loop(){
    switch (status){
    case 0:
      Serial.print("HL__");
      Serial.print(pulseIn(hintenLinks, HIGH,5000));
      Serial.print("  HR__");
      Serial.print(pulseIn(hintenRechts, HIGH,5000));
      Serial.print("  VL__");
      Serial.print(pulseIn(vorneLinks, HIGH,5000));
      Serial.print("  VR__");
      Serial.println(pulseIn(vorneRechts, HIGH,5000));
    break;
    case 1:
    Serial.print("HL__");
      Serial.print((float)1000/( (float)pulseIn(hintenLinks, HIGH,5000) / (float)500));
      Serial.print("  HR__");
      Serial.print((float)1000/( (float)pulseIn(hintenRechts, HIGH,5000) / (float)500));
      Serial.print("  VL__");
      Serial.print((float)1000/( (float)pulseIn(vorneLinks, HIGH,5000) / (float)500));
      Serial.print("  VR__");
      Serial.println((float)1000/( (float)pulseIn(vorneRechts, HIGH,5000) / (float)500));
    break;
    }
}


