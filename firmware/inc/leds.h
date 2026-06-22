#pragma once
#include <FastLED.h>
#include <cstdint>

namespace leds {
void init();
void set(uint8_t index, CRGB color);
void clear();
} // namespace leds
