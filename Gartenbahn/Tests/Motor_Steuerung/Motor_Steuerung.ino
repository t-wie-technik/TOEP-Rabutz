int pwm = 19;//12;
int dir = 13;//11;
int zeit = 50;
int dir_int =1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pwm,OUTPUT);
  pinMode(dir,OUTPUT);
 
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 switch (dir_int) {
  case 0:
    analogWrite(dir,255);
    dir_int = 1;
    break;
  case 1:
    analogWrite(dir,0);
    dir_int = 0;
    break;
 }
 
  for (int i =0 ; i< 255;i++){
  analogWrite(pwm,i);
  delay(zeit);
 }
 delay(4000);
 
 for (int i =255 ; i> 0;i--){
  analogWrite(pwm,i);
  delay(zeit);
 }
  
  }
