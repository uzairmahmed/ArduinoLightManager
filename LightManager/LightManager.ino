#include <SoftwareSerial.h> // Import SoftwareSerial Library for PWM TX and RX pins.
#include <LiquidCrystal.h> // Import LiquidCrystal Library for LCD display

SoftwareSerial bt(10,11); //Declare HC-05's TX and RX pins, respectively.
LiquidCrystal lcd(2,3,4,5,6,7); // Declare LCD's  RS, EN, D4, D5, D6, D7 pins, respectively.


void setup() {
  lcd.begin(16,2); // Initialize LCD's 16 columns and 2 rows of pixels.
  lcd.print("Welcome.");

  Serial.begin(9600); // Begin Serial Monitor
  Serial.println("Start"); // Print Serial Confirmation

  bt.begin(38400); // Begin Bluetooth Monitor
  bt.println("BT Start"); // Print Bluetooth Confirmation
}

void loop() {
  if (bt.available()){
    Serial.write(bt.read());
  }
  if (Serial.available()){
    bt.write(Serial.read());
  }
}
