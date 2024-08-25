#include <Arduino.h>
#include <Wire.h>
#include "lcd.h"
#include "filesystem.h"
#include "input.h"
#include "midi-messaging.h"

void setup() {
    demoData();
    initFileSystem();
    initMidi();
    initInput();
    initLcd();
}

void loop() {
    loopMidi();
    loopInput();
    loopLcd();
}
