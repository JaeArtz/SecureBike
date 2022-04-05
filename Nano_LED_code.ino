#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define NEO_PINL   5  
#define NEO_PINL2  6
#define NEO_PINR   9
#define NEO_PINR2  10
#define NEO_PTYPE NEO_GRBW  // f.e. SK6812

#define BUTTON_PINL 2
#define BUTTON_PINR 4

#define NUMPIXELS 11
#define BRIGHTNESS  64 // set brightness 0-128
#define ORANGE 0x00cc6d00

#if (((NEO_PTYPE & 0xC0) >> 2) != (NEO_PTYPE & 0x30)) // check for RGBW type
#define INIT_MSG  "Strip is set to 32-bit type (RGBW)"
#else
#define INIT_MSG  "Strip is set to 24-bit type (RGB)"
#endif

uint32_t color = ORANGE;

Adafruit_NeoPixel stripL = Adafruit_NeoPixel(NUMPIXELS, NEO_PINL, NEO_PTYPE + NEO_KHZ800);
Adafruit_NeoPixel stripL2 = Adafruit_NeoPixel(NUMPIXELS, NEO_PINL2, NEO_PTYPE + NEO_KHZ800);
Adafruit_NeoPixel stripR = Adafruit_NeoPixel(NUMPIXELS, NEO_PINR, NEO_PTYPE + NEO_KHZ800);
Adafruit_NeoPixel stripR2 = Adafruit_NeoPixel(NUMPIXELS, NEO_PINR2, NEO_PTYPE + NEO_KHZ800);

void setup() {
  pinMode(BUTTON_PINL, INPUT);
  pinMode(BUTTON_PINR, INPUT);
  stripL.begin(); // This initializes the NeoPixel library.
  stripL.setBrightness(BRIGHTNESS); // set brightness
  stripL.show(); // Initialize all pixels to 'off'
  stripL2.begin(); // This initializes the NeoPixel library.
  stripL2.setBrightness(BRIGHTNESS); // set brightness
  stripL2.show(); // Initialize all pixels to 'off'
  stripR.begin(); // This initializes the NeoPixel library.
  stripR.setBrightness(BRIGHTNESS); // set brightness
  stripR.show(); // Initialize all pixels to 'off'
  stripR2.begin(); // This initializes the NeoPixel library.
  stripR2.setBrightness(BRIGHTNESS); // set brightness
  stripR2.show(); // Initialize all pixels to 'off'
}

void loop() {
  boolean stateL = digitalRead(BUTTON_PINL);
  boolean stateR = digitalRead(BUTTON_PINR);
  while(stateL == HIGH){
      stripL.setBrightness(BRIGHTNESS);
      stripL2.setBrightness(BRIGHTNESS);
      setAllPixelsL(color);
      stripL.show();
      stripL2.show();
      delay(500);
      stripL.setBrightness(0);
      stripL2.setBrightness(0);
      stripL.show();
      stripL2.show();
      delay(500);
      stateL = digitalRead(BUTTON_PINL);
  }
  while(stateR == HIGH){
      stripR.setBrightness(BRIGHTNESS);
      stripR2.setBrightness(BRIGHTNESS);
      setAllPixelsR(color);
      stripR.show();
      stripR2.show();
      delay(500);
      stripR.setBrightness(0);
      stripR2.setBrightness(0);
      stripR.show();
      stripR2.show();
      delay(500);
      stateR = digitalRead(BUTTON_PINR);
  }    
}

void setAllPixelsL(uint32_t c) {
  for(uint16_t i=0; i < stripL.numPixels(); i++) {
    stripL.setPixelColor(i, c);
  }
  for(uint16_t i=0; i < stripL2.numPixels(); i++) {
    stripL2.setPixelColor(i, c);
  }
}

void setAllPixelsR(uint32_t c) {
  for(uint16_t i=0; i < stripR.numPixels(); i++) {
    stripR.setPixelColor(i, c);
  }
  for(uint16_t i=0; i < stripR2.numPixels(); i++) {
    stripR2.setPixelColor(i, c);
  }
}
