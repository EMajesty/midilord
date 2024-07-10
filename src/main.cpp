#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal.h>

const byte rs = 6, enTop = 4, enBot= 5, d4 = 0, d5 = 1, d6 = 2, d7 = 3;

LiquidCrystal lcdTop(rs, enTop, d4, d5, d6, d7);
LiquidCrystal lcdBot(rs, enBot, d4, d5, d6, d7);

void setup() {
    lcdTop.begin(40, 2);
    lcdBot.begin(40, 2);

    lcdTop.setCursor(0, 0);
    lcdTop.print("[Preset 1] Preset 2  Preset 3   Bank +  ");
    lcdTop.setCursor(0, 1);
    lcdTop.print(" BPM 666                                ");
    lcdBot.setCursor(0, 0);
    lcdBot.print("                        |---Tap---|     ");
    lcdBot.setCursor(0, 1);
    lcdBot.print(" Preset 4  Preset 5  Preset 6   Bank -  ");
}

void loop() {
}
