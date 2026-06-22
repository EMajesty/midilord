#pragma once

#include "types.h"
#include <cstdint>

namespace midiport {
void init();
void send(types::Event event);
void sendCC(uint8_t number, uint8_t value, uint8_t channel);
void sendPC(uint8_t number, uint8_t channel);
} // namespace midiport
