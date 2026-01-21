#include <Arduino.h>
#include <FastLED.h>
#include "reference/matrixMap_32x48_3pin.h" 

#define PIN0 2
#define PIN1 3
#define PIN2 4
#define HEIGHT 32 
#define WIDTH 48
#define NUM_STRIPS 3
#define NUM_LEDS_PER_STRIP 512

using namespace fl;

#define NUM_LEDS ( WIDTH * HEIGHT )
const uint16_t MIN_DIMENSION = min(WIDTH, HEIGHT);
const uint16_t MAX_DIMENSION = max(WIDTH, HEIGHT);

CRGB leds[NUM_LEDS];
uint16_t ledNum = 0;

uint8_t BRIGHTNESS = 35;

//************************************************************************************************************

extern const uint16_t progTopDown[NUM_LEDS] PROGMEM;

uint16_t myXY(uint8_t x, uint8_t y) {
  if (x >= WIDTH || y >= HEIGHT) return 0;
  uint16_t i = ( y * WIDTH ) + x;
  ledNum = progTopDown[i];
  return ledNum;
}	


//************************************************************************************************************

void setup() {

   Serial.begin(115200);
   delay(1000);

   //FastLED.setExclusiveDriver("RMT");

   FastLED.addLeds<WS2812B, PIN0, GRB>(leds, 0, NUM_LEDS_PER_STRIP)
     .setCorrection(TypicalLEDStrip);

   FastLED.addLeds<WS2812B, PIN1, GRB>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP)
     .setCorrection(TypicalLEDStrip);
  
   FastLED.addLeds<WS2812B, PIN2, GRB>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP)
     .setCorrection(TypicalLEDStrip);

   FastLED.setBrightness(BRIGHTNESS);

   FastLED.clear();
   FastLED.show();

}

//************************************************************************************************************

void loop() {

  EVERY_N_SECONDS(2){
    Serial.println("Loop...");
  }

  static uint8_t hue = 0;
  
  fill_rainbow(leds, NUM_LEDS, hue, 7);
  FastLED.show();

  hue ++;
  
}
