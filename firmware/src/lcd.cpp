#include "lcd.h"
#include <LiquidCrystal.h>
#include <cstdint>

namespace {
const uint8_t d4 = 7, d5 = 16, d6 = 18, d7 = 17, e1 = 15, e2 = 6, rs = 5;
LiquidCrystal lcdTop = LiquidCrystal(rs, e1, d4, d5, d6, d7);
LiquidCrystal lcdBot = LiquidCrystal(rs, e2, d4, d5, d6, d7);

const char leftMarker = 0xA2, rightMarker = 0xA3;

const uint8_t bankNamePos[2] = {0, 2};
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

void vegas() {}
void clear() {}
// 0123456789012345678901234567890123456789
// x12345678xx12345678xx12345678xx12345678x
//
//
// x12345678xx12345678xx12345678xx12345678x
void drawBank(types::Bank bank) {
    lcdTop.setCursor(bankNamePos[0], bankNamePos[1]);
    lcdTop.write(bank.name);

    for (uint8_t i = 0; i < 8; i++) {
        if (i < 5) {
            lcdTop.setCursor(i * 10 + 1, 0);
            lcdTop.write(bank.presets[i].name);
        } else {
            lcdBot.setCursor((i - 4) * 10 + 1, 1);
            lcdBot.write(bank.presets[i].name);
        }
    }
}
void drawActivePreset(uint8_t index) {
    char left = ' ', right = ' ';

    for (uint8_t i = 0; i < 8; i++) {
        if (index == i) {
            left = leftMarker;
            right = rightMarker;
        } else {
            left = ' ';
            right = ' ';
        }

        if (i < 5) {
            lcdTop.setCursor((i - 1) * 10, 0);
            lcdTop.write(left);
            lcdTop.setCursor((i - 1) * 10 + 9, 0);
            lcdTop.write(right);
        } else {
            lcdBot.setCursor((i - 5) * 10, 1);
            lcdBot.write(left);
            lcdBot.setCursor((i - 5) * 10 + 9, 1);
            lcdBot.write(right);
        }
    }
}

} // namespace lcd
