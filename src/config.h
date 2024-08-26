#pragma once

#include <Arduino.h>

const byte BANKS_MAX = 30;
const byte MESSAGES_MAX = 30;

struct Message {
    byte type;
    byte channel; // PC, CC
    byte number; // PC, CC
    byte value; // CC
};

struct Preset {
    char name[8];
    Message messages[MESSAGES_MAX];
};

struct Bank {
    char name[8];
    Preset presets[8];
};

extern struct Config {
    Bank banks[BANKS_MAX];
    byte currentBank = 0;
    byte currentPreset = 0;
    int bpm;
} config;


enum MessageType {
    INTERNAL,
    CONTROL,
    PROGRAM
};

void demoData();
