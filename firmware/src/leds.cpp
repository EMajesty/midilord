#include "leds.h"
#include <FastLED.h>
#include <cstdint>

namespace {
const uint8_t LED_PIN = 4;
const uint8_t LED_COUNT = 9;
const uint8_t BUTTON_LEDS = 8;
const uint8_t UI_LED_INDEX = 9;
CRGB indicators[LED_COUNT];
} // namespace

namespace leds {
void init() { FastLED.addLeds<WS2812B, LED_PIN, RGB>(indicators, LED_COUNT); }

void set(uint8_t index, CRGB color) {
    indicators[index] = color;
    FastLED.show();
}

void clear() {
    for (int i = 0; i < BUTTON_LEDS; i++) {
        indicators[i] = CRGB(0, 0, 0);
    }
    FastLED.show();
}
} // namespace leds
