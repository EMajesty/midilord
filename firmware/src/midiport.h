#pragma once

#include "types.h"

namespace midiport {
void init();
void send(types::Event);
} // namespace midiport
