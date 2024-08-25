#pragma once

#include <Arduino.h>

#define BANKS_MAX 30
#define MESSAGES_MAX 30

// ---------- Presets ---------------------------------------------------------
// bank[preset1, ..., preset8]
// preset[message, message, ...]
// message[type, channel, programnumber/controlnumber, controlvalue]
struct Message {
    byte type;
    byte channel;
    byte number;
    byte value;
};

struct Preset {
    char name[8];
    Message messages[MESSAGES_MAX];
};

struct Bank {
    char name[8];
    Preset presets[8];
};

struct Config {
    Bank banks[BANKS_MAX];
    byte currentBank = 0;
    byte currentPreset;
    int bpm;
} config;

enum MessageType {
    INTERNAL,
    CONTROL,
    PROGRAM
};


