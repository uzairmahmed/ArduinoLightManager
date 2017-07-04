#include <LiquidCrystal.h> // Import LiquidCrystal Library for LCD display
#include <Adafruit_NeoPixel.h>

//#include <Wire.h>
//#include "Nunchuk.h"

#define PIN 9
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Declare LCD's  RS, EN, D4, D5, D6, D7 pins, respectively.

int input = 0;
int uiState = 1;
int lightMode = 0;

byte smiley[]      = {B01010, B01010, B01010, B00000, B11111, B10001, B10001, B01110};
byte upArrow[]     = {B11111, B11011, B10001, B00000, B11011, B11011, B11011, B11111};
byte downArrow[]   = {B11111, B11011, B11011, B11011, B00000, B10001, B11011, B11111};
byte leftArrow[]   = {B11111, B11011, B10011, B00000, B00000, B10011, B11011, B11111};
byte rightArrow[]  = {B11111, B11011, B11001, B00000, B00000, B11001, B11011, B11111};

/*int Razz [3]= {227, 11, 22};    int Mage [3]= {238, 0, 238};  int Purp [3]= {148, 0, 211};
int LPurp [3]= {132, 112, 255};  int Blue [3]= { 0, 0, 255};   int RBlu [3]= { 72, 118, 255};
int Turq [3]= { 0, 245, 255};   int DGre [3]= { 0, 201, 87};  int Gree [3]= { 0, 255, 0};
int Lime [3]= {124, 252, 0};    int Yell [3]= {255, 255, 0};  int Oran [3]= {255, 165, 0};
int DOran [3]= {255, 127, 0};    int OrRed [3]= {255, 69, 0};   int Red [3]= {255, 0, 0};
int DRed [3]= {139, 0, 0};      //int DarkBlack [3]= {-255,-255,-255}; <--Thats a joke dont worry.
int* colors[16] = {Razz,Mage,Purp,LPurp,Blue,RBlu,Turq,DGre,Gree,Lime,Yell,Oran,DOran,OrRed,Red,DRed};

int color1Index = 0; int color2Index = 0; int color3Index = 0;*/

int r1 = 255; int g1 = 0; int b1 = 0; String col1Name = "red";
int r2 = 0; int g2 = 0; int b2 = 255; String col2Name = "blue";
int lightSpeed = 50;


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
  strip.setBrightness(32);
}


void loop() {
  if (Serial.available() > 0) {
    input = Serial.parseInt();
    Serial.println(input);
  }

  menuManager();
  settingManager();
  controlManager();

}


