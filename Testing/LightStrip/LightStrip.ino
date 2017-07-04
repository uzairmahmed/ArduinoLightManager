#include <Adafruit_NeoPixel.h>

#define PIN 9
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
    
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(150);
}

void loop() {
  scrollNewCol();
}

void scrollNewCol(){
  for (int x = 0; x < 60; x++) {
    strip.setPixelColor(x, 255,0,0);
    delay(15);
    strip.show();
  }
  for (int y = 60; y > 0; y--) {
    strip.setPixelColor(y, 255,50,0);
    delay(15);
    strip.show();
  }
    for (int x = 0; x < 60; x++) {
    strip.setPixelColor(x, 255,255,0);
    delay(15);
    strip.show();
  }
  for (int y = 60; y > 0; y--) {
    strip.setPixelColor(y, 0,255,0);
    delay(15);
    strip.show();
  }
    for (int x = 0; x < 60; x++) {
    strip.setPixelColor(x, 50,255,50);
    delay(15);
    strip.show();
  }
  for (int y = 60; y > 0; y--) {
    strip.setPixelColor(y, 0,0,255);
    delay(15);
    strip.show();
  }
    for (int x = 0; x < 60; x++) {
    strip.setPixelColor(x, 255,0,255);
    delay(15);
    strip.show();
  }
}

