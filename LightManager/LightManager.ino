#include <LiquidCrystal.h> // Import LiquidCrystal Library for LCD display
#include <Adafruit_NeoPixel.h>

#include <Wire.h>

#define PIN 9
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Declare LCD's  RS, EN, D4, D5, D6, D7 pins, respectively.

int buttonPin = 11;
int input = 0;
int state = 1;
int lightMode = 0;
int lightSpeed = 10;
int buttonState = 0;


int r1 = 0 ; int g1 = 0; int b1 = 0; String col1Name = "null";
int r2 = 0; int g2 = 0; int b2 = 0; String col2Name = "null"; 

void setup() {
  lcd.begin(16, 2); // Initialize LCD's 16 columns and 2 rows of pixels.
  lcd.print("Welcome.");

  Serial.begin(9600); // Begin Serial Monitor
  Serial.println("Start"); // Print Serial Confirmation

  pinMode(buttonPin,INPUT);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(150);
}


void loop() {
  lightManager();
  colorManager();
}


