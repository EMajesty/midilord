#pragma once

#include <FastLED.h>
#include <cstdint>

namespace types {
enum EventType { NONE, INTERNAL, CC, PC };
enum Output { ALL, M1, M2 };
struct Event {
    EventType type;
    uint8_t message;
    uint8_t value;
    uint8_t channel;
    Output output = ALL;
};
struct Preset {
    char name[7]; // 6 characters + null terminator
    Event events[16];
    CRGB color = CRGB(128, 128, 0);
};
struct Bank {
    Preset presets[8];
};
} // namespace types
