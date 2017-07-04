#include <Wire.h>
#include "Nunchuk.h"

void setup() {

    Serial.begin(9600);
    Wire.begin();
    pinMode(13, OUTPUT);
    //nunchuk_init_power(); // A1 and A2 is power supply
    nunchuk_init();
}

void loop() {
    Serial.println("Begin Loop");
    if (nunchuk_read()) {
      Serial.println("Inside if num read");
        // Work with nunchuk_data
        nunchuk_print();
        Serial.println("end of num print command and if");
    } else{
      nunchuk_init();
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);  
    }
    
    } 
