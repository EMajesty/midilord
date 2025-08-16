#pragma once

#include <Arduino.h>

void initLcd();
void loopLcd();
void drawHello();
void drawPresets();
void drawActivePreset(byte activePreset);
void drawCurrentBank();
void drawBPM();
void drawClick();
