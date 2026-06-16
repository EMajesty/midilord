#include "event.h"
#include "lcd.h"
#include "leds.h"
#include "midiport.h"
#include "storage.h"
#include "switches.h"
#include <Arduino.h>

void setup() {
    Serial.begin(115200);

    delay(3000);

    storage::init();
    switches::init();
    midiport::init();
    event::init();
    leds::init();
    lcd::init();
    lcd::drawBank(storage::currBank);
    leds::clear();
}

void loop() { switches::read(); }
