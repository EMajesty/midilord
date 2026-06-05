#include "leds.h"
#include <FastLED.h>
#include <cstdint>

namespace {
const uint8_t LED_PIN = 4;
const uint8_t LED_COUNT = 8;
CRGB indicators[LED_COUNT];
} // namespace

namespace leds {
void init() { FastLED.addLeds<WS2812B, LED_PIN, RGB>(indicators, LED_COUNT); }

void vegas() {
    for (int i = 0; i < LED_COUNT; i++) {
        indicators[i] = CRGB(255, 0, 0);
    }
    FastLED.show();
}

void set(uint8_t index, CRGB color) {
    indicators[index] = color;
    FastLED.show();
}

void setClear(uint8_t index, CRGB color) {
    for (int i = 0; i < LED_COUNT; i++) {
        indicators[i] = CRGB(0, 0, 0);
    }
    indicators[index] = color;
    FastLED.show();
}
} // namespace leds
