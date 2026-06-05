#include "lcd.h"
#include "leds.h"
#include "switches.h"
#include <Arduino.h>

void setup() {
    Serial.begin(115200);

    leds::init();
    lcd::init();
    switches::init();
    lcd::test();
}

void loop() { switches::read(); }
