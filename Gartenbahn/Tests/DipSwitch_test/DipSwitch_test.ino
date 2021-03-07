//Documentation
/*  1   |  2  |  3 
    on  | off | off   = 890 / 891
    off | on  | off   = 466 / 467
    off | off | on    = 128 / 129
    on  | on  | on    = 105 / 106
    off | off | off   = 1023
    on  | on  | off   = 400 / 401
    on  | off | on    = 122 / 123
    off | on  | on    = 109 / 110 */
    
void setup() {
  Serial.begin(9600);
  pinMode(A0,INPUT);
  
}

void loop() {
  Serial.println(analogRead(A0));
}
