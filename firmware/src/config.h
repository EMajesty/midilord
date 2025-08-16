#pragma once

#include <Arduino.h>

const byte BANKS_MAX = 30;
const byte MESSAGES_MAX = 30;

struct Message {
    byte type = 0;
    byte channel = 0; // PC, CC
    byte number = 0; // PC, CC
    byte value = 0; // CC
};

struct Preset {
    char name[8] = {0};
    Message messages[MESSAGES_MAX];
};

struct Bank {
    char name[8] = {0};
    Preset presets[8];
};

extern struct Config {
    Bank banks[BANKS_MAX];
    byte currentBank = 0;
    byte currentPreset = 0;
    int bpm = 0;
} config;


enum MessageType {
    EMPTY,
    INTERNAL,
    CONTROL,
    PROGRAM
};

void demoData();
