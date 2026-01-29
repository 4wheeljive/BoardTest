#include <Arduino.h>
#include <FastLED.h>
//#include "platforms/esp/32/drivers/rmt/rmt_5/rmt_memory_manager.h"
//#include "esp_log.h"
#include "reference/matrixMap_32x48_3pin.h"
//#include "reference/matrixMap_22x22.h" 

#define PIN0 2
#define PIN1 3
#define PIN2 4
#define HEIGHT 32 
#define WIDTH 48
#define NUM_STRIPS 3
#define NUM_LEDS_PER_STRIP 512
//#define HEIGHT 22 
//#define WIDTH 22
//#define NUM_STRIPS 1
//#define NUM_LEDS_PER_STRIP 484

//using namespace fl;

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

   // Suppress ESP-IDF cache sync errors early (before any FastLED init)
   //esp_log_level_set("cache", ESP_LOG_NONE);
   //esp_log_level_set("rmt", ESP_LOG_NONE);

   Serial.begin(115200);
   delay(1000);

   // Reserve external RMT memory usage (USB CDC or other drivers)
   //auto& rmtMgr = fl::RmtMemoryManager::instance();
   //rmtMgr.reserveExternalMemory(48, 0);

   FastLED.setDriverEnabled("SPI", false); 
   FastLED.setDriverEnabled("UART", false);
   FastLED.setDriverEnabled("I2S", false);
   FastLED.setDriverEnabled("I2S LCD_CAM", false);
   FastLED.setExclusiveDriver("RMT");

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
  
  /*
  EVERY_N_SECONDS(3) {
    //FASTLED_DBG("Loop...");
    uint8_t fps = FastLED.getFPS();
    FASTLED_DBG(fps << " fps");
  }
  */

  static uint8_t hue = 0;
  
  fill_rainbow(leds, NUM_LEDS, hue, 7);
  FastLED.show();

  hue ++;
  
}
