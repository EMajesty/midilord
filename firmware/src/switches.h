#pragma once

#include <Keypad.h>

namespace {
void keypadEvent(KeypadEvent key);
}

namespace switches {
void init();
void read();
} // namespace switches
