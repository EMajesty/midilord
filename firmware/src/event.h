#pragma once

#include <cstdint>

namespace event {
void init();
void trigger(uint8_t key);
void changeBank(uint8_t bank);
} // namespace event
