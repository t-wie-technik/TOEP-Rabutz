

//LEDs
void ledRot1 (bool dir){
    switch (dir) {
        case 0:
            digitalWrite(rot1PwmPin, LOW);
        break;
        case 1:
            digitalWrite(rot1PwmPin, HIGH);
        break;
    }
}
void ledRot2 (bool dir){
    switch (dir) {
        case 0:
            digitalWrite(rot2PwmPin, LOW);
            digitalWrite(rot2DirPin, LOW);
        break;
        case 1:
            digitalWrite(rot2PwmPin, HIGH);
            digitalWrite(rot2DirPin, LOW);
        break;
    }
}
void ledRot3 (bool dir){
    switch (dir) {
        case 0:
            digitalWrite(rot3PwmPin, LOW);
            digitalWrite(rot3DirPin, LOW);
        break;
        case 1:
            digitalWrite(rot3PwmPin, HIGH);
            digitalWrite(rot3DirPin, LOW);
        break;
    }
}
void ledRot4 (bool dir){
    switch (dir) {
        case 0:
            digitalWrite(rot4PwmPin, LOW);
            digitalWrite(rot4DirPin, LOW);
        break;
        case 1:
            digitalWrite(rot4PwmPin, HIGH);
            digitalWrite(rot4DirPin, LOW);
        break;
    }
}
void ledRot5 (bool dir){
    switch (dir) {
        case 0:
            digitalWrite(rot5PwmPin, LOW);
            digitalWrite(rot5DirPin, LOW);
        break;
        case 1:
            digitalWrite(rot5PwmPin, HIGH);
            digitalWrite(rot5DirPin, LOW);
        break;
    }
}
void ledGelb (bool dir){
    switch (dir) {
        case 0:
            digitalWrite(rot2PwmPin, LOW);
            digitalWrite(rot2DirPin, HIGH);
        break;
        case 1:
            digitalWrite(rot2PwmPin, HIGH);
            digitalWrite(rot2DirPin, HIGH);
        break;
    }
}
void ledGruen (bool dir){
    switch (dir) {
        case 0:
            digitalWrite(rot2PwmPin, LOW);
            digitalWrite(rot2DirPin, HIGH);
        break;
        case 1:
            digitalWrite(rot2PwmPin, HIGH);
            digitalWrite(rot2DirPin, HIGH);
        break;
    }
}
