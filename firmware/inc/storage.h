#pragma once

#include "types.h"
#include <cstdint>

namespace storage {
extern types::Bank currBank; // global data of current bank in memory
void init();
void getBank(uint8_t bank);
void nextBank();
void prevBank();
void writeBank();
} // namespace storage
