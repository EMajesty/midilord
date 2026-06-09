#pragma once

#include "types.h"
#include <cstdint>

namespace storage {
extern types::Bank currBank; // global data of current bank in memory
void init();
void getBank(uint8_t bank);
void getNextBank();
void getPrevBank();
void writeBank();
} // namespace storage
