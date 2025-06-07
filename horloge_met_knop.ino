#include <FastLED.h>

#define LED_PIN A2
#define NUM_LEDS 28
#define EN_LED_PIN A1
#define BRIGHTNESS 10
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define SW1 A4
#define SW4 A7
#define SW3 A6
#define SW2 A5
#define BLINK_INTERVAL 500
#define ANIMATION_INTERVAL 100

CRGB leds[NUM_LEDS];
bool StateSW1 = false;
bool lastStateSW1 = false;
bool StateSW4 = false;
bool lastStateSW4 = false;
bool StateSW3 = false;
bool lastStateSW3 = false;
bool StateSW2 = false;
bool lastStateSW2 = false;
bool colorModus = false;
bool blinkMode = false;
bool animationMode = false;
unsigned long lastBlinkTime = 0;
bool blinkState = false;
unsigned long lastAnimationTime = 0;
int animationPos = 0;
bool animationDirection = true;
uint8_t brightness = BRIGHTNESS;

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(EN_LED_PIN, OUTPUT);
  digitalWrite(EN_LED_PIN, HIGH);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  delay(2000);
}

void loop() {
  bool waardeSW1 = digitalRead(SW1);
  if (waardeSW1 != lastStateSW1) {
    delay(100);
    waardeSW1 = digitalRead(SW1);
    if (waardeSW1 == LOW && lastStateSW1 == HIGH) {
      colorModus = !colorModus;
    }
  }
  lastStateSW1 = waardeSW1;

  bool waardeSW2 = digitalRead(SW2);
  if (waardeSW2 != lastStateSW2) {
    delay(100);
    waardeSW2 = digitalRead(SW2);
    if (waardeSW2 == LOW && lastStateSW2 == HIGH) {
      if (brightness < 255 - 20) brightness += 20;
      else brightness = 20;
      FastLED.setBrightness(brightness);
    }
  }
  lastStateSW2 = waardeSW2;

  bool waardeSW3 = digitalRead(SW3);
  if (waardeSW3 != lastStateSW3) {
    delay(100);
    waardeSW3 = digitalRead(SW3);
    if (waardeSW3 == LOW && lastStateSW3 == HIGH) {
      animationMode = !animationMode;
      if (animationMode) blinkMode = false;
    }
  }
  lastStateSW3 = waardeSW3;

  bool waardeSW4 = digitalRead(SW4);
  if (waardeSW4 != lastStateSW4) {
    delay(100);
    waardeSW4 = digitalRead(SW4);
    if (waardeSW4 == LOW && lastStateSW4 == HIGH) {
      blinkMode = !blinkMode;
      if (blinkMode) animationMode = false;
    }
  }
  lastStateSW4 = waardeSW4;

  if (blinkMode) {
    if (millis() - lastBlinkTime >= BLINK_INTERVAL) {
      blinkState = !blinkState;
      lastBlinkTime = millis();
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      if (blinkState) {
        leds[i] = (i % 2 == 0) ? (colorModus ? CRGB::Blue : CRGB::Red) : CRGB::Black;
      } else {
        leds[i] = (i % 2 == 0) ? CRGB::Black : (colorModus ? CRGB::White : CRGB::Green);
      }
    }
  } else if (animationMode) {
    if (millis() - lastAnimationTime >= ANIMATION_INTERVAL) {
      if (animationDirection) {
        animationPos++;
        if (animationPos >= NUM_LEDS - 1) animationDirection = false;
      } else {
        animationPos--;
        if (animationPos <= 0) animationDirection = true;
      }
      lastAnimationTime = millis();
    }
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = (i == animationPos) ? (colorModus ? CRGB::Blue : CRGB::Red) : CRGB::Black;
    }
  } else {
    for (int i = 0; i < NUM_LEDS; i++) {
      if (colorModus) {
        leds[i] = (i % 2 == 0) ? CRGB::Blue : CRGB::White;
      } else {
        leds[i] = (i % 2 == 0) ? CRGB::Red : CRGB::Green;
      }
    }
  }
  FastLED.show();
  delay(10);
}