#include <LiquidCrystal.h> // Import LiquidCrystal Library for LCD display
#include <Adafruit_NeoPixel.h>

#include <Wire.h>
#include "Nunchuk.h"

#define PIN 9
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Declare LCD's  RS, EN, D4, D5, D6, D7 pins, respectively.

int input = 0;
int uiState = 1;
int lightMode = 0;
int lightSpeed = 15;
int color1Index = 0; int color2Index = 4;
int r1 = 0 ; int g1 = 0; int b1 = 0; String col1Name = "null";
int r2 = 0; int g2 = 0; int b2 = 0; String col2Name = "null";

byte smiley[]      = {B01010, B01010, B01010, B00000, B11111, B10001, B10001, B01110};
byte upArrow[]     = {B11111, B11011, B10001, B00000, B11011, B11011, B11011, B11111};
byte downArrow[]   = {B11111, B11011, B11011, B11011, B00000, B10001, B11011, B11111};
byte leftArrow[]   = {B11111, B11011, B10011, B00000, B00000, B10011, B11011, B11111};
byte rightArrow[]  = {B11111, B11011, B11001, B00000, B00000, B11001, B11011, B11111};

void setup() {
  lcd.begin(16, 2); // Initialize LCD's 16 columns and 2 rows of pixels.
  lcd.print("Welcome.");

  Serial.begin(9600); // Begin Serial Monitor
  Serial.println("Start"); // Print Serial Confirmation

  //Wire.begin();
  //nunchuk_init();

  lcd.createChar(5, smiley);
  lcd.createChar(1, upArrow);
  lcd.createChar(2, downArrow);
  lcd.createChar(3, leftArrow);
  lcd.createChar(4, rightArrow);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(150);
}


void loop() {
  serialInputManager();
  lightManager();
  colorManager();
  menuManager();
  settingManager();
  //nunchuckManager();
}


