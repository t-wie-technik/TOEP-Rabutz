int counter = 1;
const byte interruptPin = 18;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
attachInterrupt(18, test, FALLING);



}

void loop(){
    Serial.println(counter);
    counter = counter+1;
    delay(2000);
}


void test (){
    //volatile float freq  = (volatile float)1000/( (volatile float)pulseIn(A0, HIGH,5000) / (volatile float)500);
    Serial.println("Interrupt!");
}