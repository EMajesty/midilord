#pragma once

#include <Arduino.h>

void initMidi();
void loopMidi();
void presetToByteArray(byte preset, byte presetArray[], int length);
void sendBank(byte bank);
void handleSystemExclusive(byte *array, unsigned int size);
byte calculateChecksum(int len, byte *ptr);
void executeCommand(byte presetNum);
