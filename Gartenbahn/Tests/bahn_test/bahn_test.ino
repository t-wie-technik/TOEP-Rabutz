char* fbn[] = {"V36-left","V36-STOP","V36-right","BR640-left","BR640-STOP","BR640-right"};
int   fbi[] = {15, 25, 18, 19, 20, 21};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 6; i++) {
    pinMode(fbi[i], INPUT);
  }
  pinMode(36, OUTPUT);
}

void loop() {
  for (int i = 0; i < 6; i++) {
    bool taster(digitalRead(fbi[i]));
    if (taster == 0) {
      Serial.println(fbn[i]);
      digitalWrite(36, HIGH);
      delay(200);
      digitalWrite(36, LOW);
    }
  }
  delay(20);
}
