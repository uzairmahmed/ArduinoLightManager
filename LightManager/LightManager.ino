#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    9    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(100);
}

void loop() {
  for (int x = 0; x < 60; x++) {
    strip.setPixelColor(x, c[0], c[1], c[2]);
    delay(s);
    strip.show();
  }
  //blendscroll(1);
}


void scrollNewCol(int c[], int s) {
  for (int x = 0; x < 60; x++) {
    strip.setPixelColor(x, c[0], c[1], c[2]);
    delay(s);
    strip.show();
  }
}

int DGre [3] = {  0, 117,  19};
int Razz [3] = {227,  11,  92};
int  Red [3] = {255,   0,   0};
int Yell [3] = {255, 255,   0};
int Blue [3] = {  0,   0, 255};
int LBlu [3] = {  0, 255, 255};
int REE [3] = {  255, 0,255};

void blendscroll(int s) {
  scrollNewCol(Red, s);
  scrollNewCol(Yell, s);
  scrollNewCol(DGre, s);
  scrollNewCol(LBlu, s);
  scrollNewCol(Blue, s);
  scrollNewCol(Razz, s);
}
