#include "lcd.h"
#include <LiquidCrystal.h>
#include "config.h"

const byte rs = 16, enTop = 15, enBot= 14, d4 = 13, d5 = 12, d6 = 11, d7 = 10;

LiquidCrystal lcdTop(rs, enTop, d4, d5, d6, d7);
LiquidCrystal lcdBot(rs, enBot, d4, d5, d6, d7);

void initLcd() {
    lcdTop.begin(40, 2);
    lcdBot.begin(40, 2);

    drawHello();
    delay(3000);
    lcdTop.clear();
    lcdBot.clear();
    drawPresets();
}

void loopLcd() {
    drawBPM();
}

void drawHello() {
    lcdTop.setCursor(0, 0);
    lcdTop.print("          H E L L    W O R L D          ");
    lcdTop.setCursor(0, 1);
    lcdTop.print("           M I D I    L O R D           ");
    lcdBot.setCursor(0, 0);
    lcdBot.print("    E L E C T R I C    M A J E S T Y    ");
    lcdBot.setCursor(0, 1);
    lcdBot.print("                  2024                  ");
}

void drawPresets() {
    lcdTop.setCursor(1, 0);
    lcdTop.print(config.banks[config.currentBank].presets[0].name);
    lcdTop.setCursor(11, 0);
    lcdTop.print(config.banks[config.currentBank].presets[1].name);
    lcdTop.setCursor(21, 0);
    lcdTop.print(config.banks[config.currentBank].presets[2].name);
    lcdTop.setCursor(31, 0);
    lcdTop.print(config.banks[config.currentBank].presets[3].name);
    lcdBot.setCursor(1, 1);
    lcdBot.print(config.banks[config.currentBank].presets[4].name);
    lcdBot.setCursor(11, 1);
    lcdBot.print(config.banks[config.currentBank].presets[5].name);
    lcdBot.setCursor(21, 1);
    lcdBot.print(config.banks[config.currentBank].presets[6].name);
    lcdBot.setCursor(31, 1);
    lcdBot.print(config.banks[config.currentBank].presets[7].name);
}

void drawActivePreset(byte activePreset) {
    lcdTop.setCursor(0, 0);
    if (activePreset == 1) {
        lcdTop.print("[");
    } else {
        lcdTop.print(" ");
    }
    lcdTop.setCursor(9, 0);
    if (activePreset == 1) {
        lcdTop.print("]");
    } else {
        lcdTop.print(" ");
    }
    lcdTop.setCursor(10, 0);
    if (activePreset == 2) {
        lcdTop.print("[");
    } else {
        lcdTop.print(" ");
    }
    lcdTop.setCursor(19, 0);
    if (activePreset == 2) {
        lcdTop.print("]");
    } else {
        lcdTop.print(" ");
    }
    lcdTop.setCursor(20, 0);
    if (activePreset == 3) {
        lcdTop.print("[");
    } else {
        lcdTop.print(" ");
    }
    lcdTop.setCursor(29, 0);
    if (activePreset == 3) {
        lcdTop.print("]");
    } else {
        lcdTop.print(" ");
    }
    lcdTop.setCursor(30, 0);
    if (activePreset == 4) {
        lcdTop.print("[");
    } else {
        lcdTop.print(" ");
    }
    lcdTop.setCursor(39, 0);
    if (activePreset == 4) {
        lcdTop.print("]");
    } else {
        lcdTop.print(" ");
    }
    lcdBot.setCursor(0, 1);
    if (activePreset == 5) {
        lcdBot.print("[");
    } else {
        lcdBot.print(" ");
    }
    lcdBot.setCursor(9, 1);
    if (activePreset == 5) {
        lcdBot.print("]");
    } else {
        lcdBot.print(" ");
    }
    lcdBot.setCursor(10, 1);
    if (activePreset == 6) {
        lcdBot.print("[");
    } else {
        lcdBot.print(" ");
    }
    lcdBot.setCursor(19, 1);
    if (activePreset == 6) {
        lcdBot.print("]");
    } else {
        lcdBot.print(" ");
    }
    lcdBot.setCursor(20, 1);
    if (activePreset == 7) {
        lcdBot.print("[");
    } else {
        lcdBot.print(" ");
    }
    lcdBot.setCursor(29, 1);
    if (activePreset == 7) {
        lcdBot.print("]");
    } else {
        lcdBot.print(" ");
    }
    lcdBot.setCursor(30, 1);
    if (activePreset == 8) {
        lcdBot.print("[");
    } else {
        lcdBot.print(" ");
    }
    lcdBot.setCursor(39, 1);
    if (activePreset == 8) {
        lcdBot.print("]");
    } else {
        lcdBot.print(" ");
    }
}

void drawCurrentBank() {
    lcdTop.setCursor(30, 1);
    lcdTop.print("Bank: ");
    lcdTop.print(config.currentBank);
}

void drawBPM() {
    lcdTop.setCursor(0, 1);
    lcdTop.print("BPM: ");
    lcdTop.print(config.bpm);
}

void drawClick() {
}
