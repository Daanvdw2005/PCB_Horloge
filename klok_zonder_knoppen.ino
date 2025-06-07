#include <FastLED.h>

#define LED_PIN A2
#define NUM_LEDS 28
#define EN_LED_PIN A1
#define BRIGHTNESS 25
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 1000;
const int TIME_ACCELERATION = 60;
int hours = 11;
int minutes = 0;
int seconds = 0;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(EN_LED_PIN, OUTPUT);
  digitalWrite(EN_LED_PIN, HIGH);
  delay(2000);
}

void loop() {
  if (millis() - lastUpdateTime >= UPDATE_INTERVAL) {
    seconds += TIME_ACCELERATION;
    while (seconds >= 60) {
      seconds -= 60;
      minutes++;
      if (minutes >= 60) {
        minutes = 0;
        hours++;
        if (hours >= 24) {
          hours = 0;
        }
      }
    }
    lastUpdateTime = millis();
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }

  int displayHour = hours % 12;
  leds[displayHour] = CRGB::Red;

  int fiveMinutes = minutes / 5;
  leds[12 + fiveMinutes] = CRGB::Green;

  int extraMinutes = minutes % 5;
  if (extraMinutes > 0) {
    leds[24 + extraMinutes - 1] = CRGB::Blue;
  }

  FastLED.show();
  delay(10);
}