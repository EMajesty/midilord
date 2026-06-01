#include "leds.h"
#include <FastLED.h>
#include <cstdint>

namespace {
const uint8_t LED_PIN = 4;
const uint8_t LED_COUNT = 4;
CRGB indicators[LED_COUNT];
} // namespace

namespace leds {
void init() {
    FastLED.addLeds<WS2812B, LED_PIN, RGB>(indicators, LED_COUNT);
    for (int i = 0; i < LED_COUNT; i++) {
        indicators[i] = CRGB::Purple;
    }
    FastLED.show();
}
} // namespace leds
