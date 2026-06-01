#include "lcd.h"
#include "leds.h"
#include <Arduino.h>

void setup() {
    // initLcd();
    Serial.begin(115200);

    leds::init();
    lcd::init();
    lcd::test();
}

void loop() { delay(1000); }
