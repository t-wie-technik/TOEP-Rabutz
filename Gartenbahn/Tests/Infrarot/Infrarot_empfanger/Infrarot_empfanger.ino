#define hintenLinks 
#define hintenRechts
#define vorneLinks
#define vorneRechts
#define status 0



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);



}

void loop(){
    switch status{
    case 0:
      Serial.print("HL__")
      Serial.print(pulseIn(hintenLinks));
      Serial.print("  HR__")
      Serial.print(pulseIn(hintenRechts));
      Serial.print("  VL__")
      Serial.print(pulseIn(vorneLinks));
      Serial.print("  VR__")
      Serial.println(pulseIn(vorneRechts));
    break;
    case 1:
    Serial.print("HL__")
      Serial.print((float)1000/( (float)pulseIn(hintenLinks, HIGH,5000) / (float)500));
      Serial.print("  HR__")
      Serial.print((float)1000/( (float)pulseIn(hintenRechts, HIGH,5000) / (float)500));
      Serial.print("  VL__")
      Serial.print((float)1000/( (float)pulseIn(vorneLinks, HIGH,5000) / (float)500));
      Serial.print("  VR__")
      Serial.println((float)1000/( (float)pulseIn(vorneRechts, HIGH,5000) / (float)500));
    break;
    }
}


