#include <FastLED.h>

// Light Strip Data Pin
#define LED_PIN     8

// Information about the LED strip itself
#define NUM_LEDS    30
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
#define BRIGHTNESS  200
#define FORWARD 0
#define FAST 5

CRGB leds[NUM_LEDS];

#define STOP_BUTTON_PIN 3
#define PREV_BUTTON_PIN 2
#define NEXT_BUTTON_PIN 1

boolean oldPrevState = HIGH;
boolean oldNextState = HIGH;

int mode= 1;    // Currently-active animation mode, 0-9

void setup() {
  pinMode(PREV_BUTTON_PIN, INPUT_PULLUP);
  pinMode(NEXT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(STOP_BUTTON_PIN, INPUT_PULLUP);

  
  LEDS.addLeds<CHIPSET,LED_PIN,COLOR_ORDER>(leds,NUM_LEDS);
  LEDS.setBrightness(BRIGHTNESS);
  colorWipe(CRGB::Red,FORWARD,FAST);    // Black/off

  Serial.begin(9600);
}

void loop() {
  // Get current button state.
  boolean newPrevState = digitalRead(PREV_BUTTON_PIN);
  boolean newNextState = digitalRead(NEXT_BUTTON_PIN);
  boolean stopState = digitalRead(STOP_BUTTON_PIN);          
  int cycleNumber = 0;

  Serial.println(digitalRead(PREV_BUTTON_PIN));

  // Check if state changed from high to low (button press).
  if(((newPrevState == LOW) && (oldPrevState == HIGH)) || ((newNextState == LOW) && (oldNextState == HIGH))) {
      Serial.println("true");
    // Short delay to debounce button.
    delay(250);
    // Check if button is still low after debounce.
    newPrevState = digitalRead(PREV_BUTTON_PIN);
    newNextState = digitalRead(NEXT_BUTTON_PIN);

    if(newPrevState == LOW) {
      if(--mode < 0) mode = 7;
    }
    if(newNextState == LOW) {
      if(++mode > 7) mode = 0;
    }
    
    if((newPrevState == LOW) || (newNextState == LOW)) {      // Yes, still low
      switch(mode) {           // Start the new animation...
        case 0:
          colorWipe(CRGB::Black,FORWARD,FAST);    // Black/off
          break;
        case 1:
          colorWipe(CRGB::Red,FORWARD,FAST);    // Red
          break;
        case 3:
          colorWipe(CRGB::Blue,FORWARD,FAST);    // Blue
          break;
        case 4:
          colorWipe(CRGB::Green,FORWARD,FAST);    // Green
          break;
        case 5:
          colorWipe(CRGB::White,FORWARD,FAST);    // White
          break;
        case 6:
          colorWipe(CRGB::Teal,FORWARD,FAST);    // Teal
          break;
        case 7:
          colorWipe(CRGB::DeepPink,FORWARD,FAST);    // Pink  `
          break;
        case 2:
          while(mode == 2){
            rainbow(FAST);
            if((digitalRead(PREV_BUTTON_PIN) == LOW) 
                || (digitalRead(NEXT_BUTTON_PIN)==LOW)) break;
          }
          break;         
        }
      }
    }
  // Set the last-read button state to the old state.
  oldPrevState = newPrevState;
  oldNextState = newNextState;
}

void colorWipe(CRGB c, int speed, int direction){
  for(int i=0; i<NUM_LEDS; i++){
    if(direction == FORWARD){
      leds[i] = c;
    }
    else{
      leds[NUM_LEDS-1-i] = c;
    }
    FastLED.show();
    delay(speed);
  }
}

void rainbow(int speed){
  for(int j=0; j<256; j++){
    for(int i=0; i< NUM_LEDS; i++) {
      leds[i] = Wheel((i*1+j) & 255);
    }
    FastLED.show();
    delay(speed);
  }
}

void disolve(int simultaneous, int cycles, int speed){
  int value = 15;
  for(int j=0; j<simultaneous; j++){
    int idx = random(NUM_LEDS);
    leds[idx] = CRGB::Black;
    
    CRGB randomCol = randomColor();
    for(int i = 0; i < value; i++){
      leds[idx] = fadeTowardColor(leds[idx], randomCol, value);
      FastLED.show();
      delay(10);
    }
    
    for(int i = value; i > 0; i--){
      leds[idx] = fadeTowardColor(leds[idx], CRGB::Black, value);
      FastLED.show();
      delay(10);
    }
  }
}

void cylon(CRGB c, int width, int speed){
  // First slide the leds in one direction
  for(int i = 0; i <= NUM_LEDS-width; i++) {
    for(int j=0; j<width; j++){
      leds[i+j] = c;
    }

    FastLED.show();

    // now that we've shown the leds, reset to black for next loop
    for(int j=0; j<5; j++){
      leds[i+j] = CRGB::Black;
    }
    delay(speed);
  }

  // Now go in the other direction.  
  for(int i = NUM_LEDS-width; i >= 0; i--) {
    for(int j=0; j<width; j++){
      leds[i+j] = c;
    }
    FastLED.show();
    for(int j=0; j<width; j++){
      leds[i+j] = CRGB::Black;
    }

    delay(speed);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
CRGB Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return CRGB(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return CRGB(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return CRGB(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

CRGB fadeTowardColor( CRGB& cur, const CRGB& target, uint8_t amount)
{
  nblendU8TowardU8( cur.red,   target.red,   amount);
  nblendU8TowardU8( cur.green, target.green, amount);
  nblendU8TowardU8( cur.blue,  target.blue,  amount);
  return cur;
}

// Helper function that blends one uint8_t toward another by a given amount
void nblendU8TowardU8( uint8_t& cur, const uint8_t target, uint8_t amount)
{
  if( cur == target) return;
 
  if( cur < target ) {
    uint8_t delta = target - cur;
    delta = scale8_video( delta, amount);
    cur += delta;
  } else {
    uint8_t delta = cur - target;
    delta = scale8_video( delta, amount);
    cur -= delta;
  }
}


CRGB randomColor(){
  return Wheel(random(256)); 
}

void allColor(CRGB c){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = c;
  }
  FastLED.show();
}

void allRandom(){
  for(int i=0; i<NUM_LEDS; i++){
    leds[i] = randomColor();
  }
  FastLED.show(); 
}
