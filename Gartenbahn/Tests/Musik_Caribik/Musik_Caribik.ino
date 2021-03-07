/*
 * Pirates of the Caribbean Theme Song auf dem Multi Function Shield
 * von Marcus Wegener 2018-05-16
 * 
 * Code inspiriert von "Play 'Pirates of the Caribbean' Theme Song on Arduino and Buzzer"
 * Link: https://github.com/xitangg/-Pirates-of-the-Caribbean-Theme-Song
 *
 * und "Super Mario theme song w/ piezo buzzer and Arduino" von Dipto Pratyaksa
 * Link https://www.princetronics.com/supermariothemesong/
 *
 * Noten Frequenzen von Arduino Webseite
 * Link: https://www.arduino.cc/en/Tutorial/toneMelody
 */

// Defintion der Noten Frequenzen
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988

// Pinbelegung
const uint8_t BUZZER = 37;
const uint8_t LED1 = 36;

// Noten (Tonhöhe)
int notes[] = {
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_A4, NOTE_A4, 

   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,

   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_C5, NOTE_D5, NOTE_B4, NOTE_B4, 0,
   NOTE_A4, NOTE_G4, NOTE_A4, 0,
   
   NOTE_E4, NOTE_G4, NOTE_A4, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, 0, 
   NOTE_D5, NOTE_E5, NOTE_F5, NOTE_F5, 0,
   NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4, 0,
   
   NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5, 0, 
   NOTE_D5, NOTE_E5, NOTE_A4, 0, 
   NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, 0,
   NOTE_C5, NOTE_A4, NOTE_B4, 0,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4,

   NOTE_E5, 0, 0, NOTE_F5, 0, 0,
   NOTE_E5, NOTE_E5, 0, NOTE_G5, 0, NOTE_E5, NOTE_D5, 0, 0,
   NOTE_D5, 0, 0, NOTE_C5, 0, 0,
   NOTE_B4, NOTE_C5, 0, NOTE_B4, 0, NOTE_A4

};

// Notenwerte (Tondauer)
// Um die Tondauer zu berechnen, 
// nehmen eine Sekunde, geteilt durch den Notentyp
// z.B. viertel Note = 1000 / 4, Achtel Note = 1000/8, etc.
int duration[] = {
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,

  250, 125,

  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 375, 125, 
  
  125, 125, 250, 125, 125, 
  125, 125, 250, 125, 125,
  125, 125, 250, 125, 125,
  125, 125, 125, 250, 125,

  125, 125, 250, 125, 125, 
  250, 125, 250, 125, 
  125, 125, 250, 125, 125,
  125, 125, 375, 375,
  
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500,

  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 125, 125, 125, 375,
  250, 125, 375, 250, 125, 375,
  125, 125, 125, 125, 125, 500

};


void setup() {
  // I/O-Pin als Ausgang
  pinMode(LED1, OUTPUT);      
  pinMode(BUZZER, OUTPUT);

  digitalWrite(LED1, HIGH);   // LED aus
  digitalWrite(BUZZER, HIGH); // BUZZER aus (Low-Aktiv)
}

void loop() {
    int size = sizeof(notes) / sizeof(int);
    for (int thisNote = 0; thisNote < size ; thisNote++) {
      int noteDuration = duration[thisNote];
 
      buzz(notes[thisNote], noteDuration);
 
      // Um die Noten zu unterscheiden, wird eine Mindestzeit zwischen ihnen festgelegt.
      int pauseBetweenNotes = noteDuration * 0.5;
      delay(pauseBetweenNotes);
    }
}

void buzz(long frequency, long length) {
  digitalWrite(LED1, LOW); // LED AN
  long delayValue = 1000000 / frequency / 2; // Berechnung des Verzögerungswertes zwischen den Übergängen
  // 1 Sekunde in Mikrosekunden, geteilt durch die Frequenz und dann halbiert, da zu jedem Zyklus zwei Phasen vorhanden sind
  long numCycles = frequency * length / 1000; // Berechnung der Anzahl der Zyklen für das richtige Timing
  // Frequenz, die die wirklichen Zyklen pro Sekunde ist, multipliziert mit der Anzahl der Sekunden,um die Gesamtzahl der Zyklen zu erhalten
    for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(BUZZER, LOW); // BUZZER an
    delayMicroseconds(delayValue); // warten auf den berechneten Verzögerungswert
    digitalWrite(BUZZER, HIGH); // BUZZER aus
    delayMicroseconds(delayValue); // warten auf den berechneten Verzögerungswert
  }
  digitalWrite(LED1, HIGH); // LED AUS  
}  
