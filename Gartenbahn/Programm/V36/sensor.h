void readSensorSlow(){
    switch (driveDir){
        case 0:
            if (readSensor(slowFrontPin) = true){
                driveAction - 1;
                
            
        break;
        case 1:
            if (readSensor(slowBackPin) = true){
                driveAction - 1;
                
            }
        break;
    }
}

void readSensorFast(){
    switch (driveDir){
        case 0:
            if (readSensor(fastFrontPin) = true){
                driveAction + 1;
                
            }
        break;
        case 1:
            if (readSensor(fastBackPin) = true){
                driveAction + 1;
                
            }
        break;
    }
}

///Frequenzmesser
bool readSensor (int pin){
    float freq_in = (float)1000/( (float)pulseIn(pin, HIGH,5000) / (float)500);
    if (freq_in < freq_max && freq_in > freq_min){
        return true;
    }else {
        return false;
    }
}