int pin1 = 12; //letzter
int pin2 = 11;

void setup() {
  // put your setup code here, to run once:
pinMode (pin1,OUTPUT);
pinMode (pin2,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  /*for (int i=0;i<150;i++){
    analogWrite (37,i);
    delay(50);
  }
  
  for (int i=150;i>0;i--){
    analogWrite (37,i);
    delay(50);
  }*/
 analogWrite (pin1,100);
 delay(2000);
 analogWrite (pin1,250);
 delay(2000);
 
 analogWrite (pin2,0);

}
