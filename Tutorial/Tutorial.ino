void setup() {
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int alf=0;alf<500;alf++){
  Serial.println(alf);
  delay(10);
  }
}
