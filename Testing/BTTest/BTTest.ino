#include <SoftwareSerial.h>
SoftwareSerial BTSerial(11, 10); // RX | TX

void setup(){
 Serial.begin(38400);
 Serial.println("SerialStart");
 BTSerial.begin(38400);
 BTSerial.println("BTStart:");
 pinMode(13, OUTPUT);
 }

void loop() {
  if (BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  if (Serial.available()){
    BTSerial.write(Serial.read());
  }
}
