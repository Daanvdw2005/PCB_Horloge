#include <FastLED.h>

#define LED_PIN A2
#define NUM_LEDS 28
#define EN_LED_PIN A1
#define BRIGHTNESS 12
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 1000;
int currentOuterLed = 0;
bool ledState = false;
void setup() {
FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
FastLED.setBrightness(BRIGHTNESS);
pinMode(EN_LED_PIN, OUTPUT);
digitalWrite(EN_LED_PIN, HIGH);
fill_solid(leds, NUM_LEDS, CRGB::Black);
FastLED.show();
delay(2000);
}
void loop() {
if (millis() - lastUpdateTime >= UPDATE_INTERVAL) {
ledState = !ledState;

if (ledState) {
digitalWrite(EN_LED_PIN, LOW);
fill_solid(leds, NUM_LEDS, CRGB::Black);
leds[currentOuterLed] = CRGB::White;
} else {
digitalWrite(EN_LED_PIN, HIGH);
fill_solid(leds, NUM_LEDS, CRGB::Black);
leds[currentOuterLed] = CRGB::White;
}

currentOuterLed = (currentOuterLed + 1) % 12;
lastUpdateTime = millis();
FastLED.show();
}
}
