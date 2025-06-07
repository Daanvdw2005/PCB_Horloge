#include <FastLED.h>  // toevoegen van de FastLED-bibliotheek

#define LED_PIN A2        // LED-data
#define NUM_LEDS 28       // aantal LEDs
#define EN_LED_PIN A1     // LED-enable
#define BRIGHTNESS 10     // basishelderheid
#define LED_TYPE WS2812B  // type LED's
#define COLOR_ORDER GRB   // Kleuren
#define SW1 A4            // pinnen schakelaars
#define SW4 A7
#define SW3 A6
#define SW2 A5
#define BLINK_INTERVAL 500 // knipperen (ms)
#define ANIMATION_INTERVAL 100 // animatie (ms)

CRGB leds[NUM_LEDS];      // array LED-kleuren
bool StateSW1 = false;    // schakelaars standen
bool lastStateSW1 = false;
bool StateSW4 = false;
bool lastStateSW4 = false;
bool StateSW3 = false;
bool lastStateSW3 = false;
bool StateSW2 = false;
bool lastStateSW2 = false;
bool colorModus = false;  // Modus kleur
bool blinkMode = false;   // Modus knipperen
bool animationMode = false; // Modus animatie
unsigned long lastBlinkTime = 0; // tijdstip knipperen
bool blinkState = false;  // huidige knipperstaat
unsigned long lastAnimationTime = 0; // tijdstip animatie
int animationPos = 0;     // positie animatie
bool animationDirection = true; // richting animatie
uint8_t brightness = BRIGHTNESS; // huidige helderheid

void setup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip); // Initialiseer LEDs
  FastLED.setBrightness(BRIGHTNESS); // Stel helderheid in
  pinMode(EN_LED_PIN, OUTPUT);       // Stel LED-enable als output
  digitalWrite(EN_LED_PIN, HIGH);    // Schakel LEDs in
  pinMode(SW1, INPUT_PULLUP);        // Stel schakelaars als input met pull-up
  pinMode(SW3, INPUT_PULLUP);
  pinMode(SW4, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  delay(2000);                       // Wacht 2 seconden voor stabilisatie
}

void loop() {
  bool waardeSW1 = digitalRead(SW1); // Lees staat schakelaar 1
  if (waardeSW1 != lastStateSW1) {   // Controleer op verandering
    delay(100);                      // Debounce-vertraging
    waardeSW1 = digitalRead(SW1);    // Lees opnieuw
    if (waardeSW1 == LOW && lastStateSW1 == HIGH) { // Detecteer druk
      colorModus = !colorModus;      // Schakel kleummodus
    }
  }
  lastStateSW1 = waardeSW1;          // Update vorige staat

  bool waardeSW2 = digitalRead(SW2); // Lees staat schakelaar 2
  if (waardeSW2 != lastStateSW2) {   // Controleer op verandering
    delay(100);                      // Debounce-vertraging
    waardeSW2 = digitalRead(SW2);    // Lees opnieuw
    if (waardeSW2 == LOW && lastStateSW2 == HIGH) { // Detecteer druk
      if (brightness < 255 - 20) brightness += 20; // Verhoog helderheid
      else brightness = 20;          // Reset bij maximum
      FastLED.setBrightness(brightness); // Pas helderheid aan
    }
  }
  lastStateSW2 = waardeSW2;          // Update vorige staat

  bool waardeSW3 = digitalRead(SW3); // Lees staat schakelaar 3
  if (waardeSW3 != lastStateSW3) {   // Controleer op verandering
    delay(100);                      // Debounce-vertraging
    waardeSW3 = digitalRead(SW3);    // Lees opnieuw
    if (waardeSW3 == LOW && lastStateSW3 == HIGH) { // Detecteer druk
      animationMode = !animationMode; // Schakel animatiemodus
      if (animationMode) blinkMode = false; // Schakel knipperen uit
    }
  }
  lastStateSW3 = waardeSW3;          // Update vorige staat

  bool waardeSW4 = digitalRead(SW4); // Lees staat schakelaar 4
  if (waardeSW4 != lastStateSW4) {   // Controleer op verandering
    delay(100);                      // Debounce-vertraging
    waardeSW4 = digitalRead(SW4);    // Lees opnieuw
    if (waardeSW4 == LOW && lastStateSW4 == HIGH) { // Detecteer druk
      blinkMode = !blinkMode;        // Schakel knippermodus
      if (blinkMode) animationMode = false; // Schakel animatie uit
    }
  }
  lastStateSW4 = waardeSW4;          // Update vorige staat

  if (blinkMode) {                   // Als knippermodus actief is
    if (millis() - lastBlinkTime >= BLINK_INTERVAL) { // Controleer interval
      blinkState = !blinkState;      // Wissel knipperstaat
      lastBlinkTime = millis();      // Update tijdstip
    }
    for (int i = 0; i < NUM_LEDS; i++) { // Doorloop alle LEDs
      if (blinkState) {
        leds[i] = (i % 2 == 0) ? (colorModus ? CRGB::Blue : CRGB::Red) : CRGB::Black;
      } else {
        leds[i] = (i % 2 == 0) ? CRGB::Black : (colorModus ? CRGB::White : CRGB::Green);
      }
    }
  } else if (animationMode) {        // Als animatiemodus actief is
    if (millis() - lastAnimationTime >= ANIMATION_INTERVAL) { // Controleer interval
      if (animationDirection) {       // Beweeg naar rechts
        animationPos++;
        if (animationPos >= NUM_LEDS - 1) animationDirection = false;
      } else {                        // Beweeg naar links
        animationPos--;
        if (animationPos <= 0) animationDirection = true;
      }
      lastAnimationTime = millis();  // Update tijdstip
    }
    for (int i = 0; i < NUM_LEDS; i++) { // Doorloop alle LEDs
      leds[i] = (i == animationPos) ? (colorModus ? CRGB::Blue : CRGB::Red) : CRGB::Black;
    }
  } else {                           // Standaardmodus
    for (int i = 0; i < NUM_LEDS; i++) { // Doorloop alle LEDs
      if (colorModus) {
        leds[i] = (i % 2 == 0) ? CRGB::Blue : CRGB::White;
      } else {
        leds[i] = (i % 2 == 0) ? CRGB::Red : CRGB::Green;
      }
    }
  }
  FastLED.show();                    // Update LED-strip
  delay(10);                         // Kleine vertraging voor stabiliteit
}
