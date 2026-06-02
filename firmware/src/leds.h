#pragma once
#include <cstdint>

namespace leds {
void init();
void set(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void update();
void vegas();
} // namespace leds
