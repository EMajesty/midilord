#include "switches.h"
#include "event.h"
#include <Arduino.h>
#include <Keypad.h>
#include <cstdint>

namespace {
const uint8_t rows = 2, cols = 4;
const char keys[rows][cols] = {{'0', '1', '2', '3'}, {'4', '5', '6', '7'}};
uint8_t rowPins[rows] = {1, 2};
uint8_t colPins[cols] = {42, 41, 40, 39};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

void keypadEvent(KeypadEvent key) {
    switch (keypad.getState()) {
    case IDLE:
        break;
    case HOLD:
        break;
    case PRESSED:
        Serial.println(String(key) + " pressed");
        event::trigger(atoi(&key));
        break;
    case RELEASED:
        break;
    }
};
} // namespace

namespace switches {
void init() { keypad.addEventListener(keypadEvent); }
void read() { keypad.getKeys(); }
} // namespace switches
