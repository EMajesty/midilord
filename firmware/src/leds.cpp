#include "leds.h"
#include <FastLED.h>
#include <cstdint>

namespace {
const uint8_t LED_PIN = 4;
const uint8_t LED_COUNT = 8;
CRGB indicators[LED_COUNT];
} // namespace

namespace leds {
void init() {
    FastLED.addLeds<WS2812B, LED_PIN, RGB>(indicators, LED_COUNT);
    for (int i = 0; i < LED_COUNT; i++) {
        indicators[i] = CRGB::Green;
    }
    indicators[0].nscale8(8);
    indicators[1].nscale8(64);
    indicators[2].nscale8(8);
    indicators[3].nscale8(64);
    indicators[4].nscale8(8);
    indicators[5].nscale8(64);
    indicators[6].nscale8(8);
    indicators[7].nscale8(64);
    FastLED.show();
}

void vegas() {
    for (int i = 0; i < LED_COUNT; i++) {
        indicators[i] = CRGB(255, 0, 0);
    }
    FastLED.show();
}
} // namespace leds
