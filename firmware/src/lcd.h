#pragma once

#include "types.h"
#include <cstdint>

namespace lcd {
void init();
void test();
void vegas();
void clear();
void drawBank(types::Bank bank);
void drawActivePreset(uint8_t index);
} // namespace lcd
