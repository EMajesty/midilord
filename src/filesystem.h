#pragma once

#include <Arduino.h>
#include <LittleFS.h>
#include "config.h"

void initFileSystem();
void readFlash();
void writeFlash();
void demoData();
void removeData();
void formatFlash();

void initFileSystem() {
    LittleFS.begin();
    // readFlash();
}    

void readFlash() {
    byte byteArray[sizeof(Config)];
    
    File file = LittleFS.open("/f.txt", "r");
    file.read(byteArray, sizeof(byteArray));

    memcpy(&config, byteArray, sizeof(Config));
}

void writeFlash() {
    byte byteArray[sizeof(Config)];
    memcpy(byteArray, &config, sizeof(Config));

    File file = LittleFS.open("/f.txt", "w");
    file.write(byteArray, sizeof(byteArray));
}

void demoData() {
    strncpy(config.banks[0].presets[0].name, "kurkku", 8);
    strncpy(config.banks[0].presets[1].name, "mopo", 8);
    strncpy(config.banks[0].presets[2].name, "a", 8);
    strncpy(config.banks[0].presets[3].name, "12345678", 8);
}

void removeData() {
    strncpy(config.banks[0].presets[0].name, "        ", 8);
    strncpy(config.banks[0].presets[1].name, "        ", 8);
    strncpy(config.banks[0].presets[2].name, "        ", 8);
    strncpy(config.banks[0].presets[3].name, "        ", 8);
}

void formatFlash() {
    LittleFS.format();
}


