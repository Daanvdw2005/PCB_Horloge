#include <FastLED.h>

#define LED_PIN A2
#define NUM_LEDS 28
// #define NUM_LEDS 1
#define EN_LED_PIN A1
#define BRIGHTNESS 100
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define SW1 A4
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(EN_LED_PIN, OUTPUT);
  digitalWrite(EN_LED_PIN, HIGH);
  delay(2000);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i % 2 == 0) {
      leds[i] = CRGB::Blue;
    } else {
      leds[i] = CRGB::Blue;
    }
  }
  FastLED.show();
  // delay(1000);
}