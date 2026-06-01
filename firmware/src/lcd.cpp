#include "lcd.h"
#include <LiquidCrystal.h>
#include <cstdint>

namespace {
const uint8_t d4 = 7, d5 = 16, d6 = 18, d7 = 17, e1 = 15, e2 = 6, rs = 5;
LiquidCrystal lcdTop = LiquidCrystal(rs, e1, d4, d5, d6, d7);
LiquidCrystal lcdBot = LiquidCrystal(rs, e2, d4, d5, d6, d7);
} // namespace

namespace lcd {
void init() {
    lcdTop.begin(40, 2);
    lcdBot.begin(40, 2);
}
void test() {
    lcdTop.setCursor(1, 0);
    lcdTop.write(0xA2);
    lcdTop.print("Preset");
    lcdTop.write(0xA3);
    lcdTop.setCursor(11, 0);
    lcdTop.write(0xA2);
    lcdTop.print("Preset");
    lcdTop.write(0xA3);
    lcdTop.setCursor(21, 0);
    lcdTop.write(0xA2);
    lcdTop.print("Preset");
    lcdTop.write(0xA3);
    lcdTop.setCursor(31, 0);
    lcdTop.write(0xA2);
    lcdTop.print("Preset");
    lcdTop.write(0xA3);
    lcdBot.setCursor(1, 1);
    lcdBot.write(0xA2);
    lcdBot.print("Preset");
    lcdBot.write(0xA3);
    lcdBot.setCursor(11, 1);
    lcdBot.write(0xA2);
    lcdBot.print("Preset");
    lcdBot.write(0xA3);
    lcdBot.setCursor(21, 1);
    lcdBot.write(0xA2);
    lcdBot.print("Preset");
    lcdBot.write(0xA3);
    lcdBot.setCursor(31, 1);
    lcdBot.write(0xA2);
    lcdBot.print("Preset");
    lcdBot.write(0xA3);
}
} // namespace lcd
