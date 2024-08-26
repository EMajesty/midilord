#include "filesystem.h"
#include <Arduino.h>
#include <LittleFS.h>
#include "config.h"

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

void removeData() {
    strncpy(config.banks[0].presets[0].name, "        ", 8);
    strncpy(config.banks[0].presets[1].name, "        ", 8);
    strncpy(config.banks[0].presets[2].name, "        ", 8);
    strncpy(config.banks[0].presets[3].name, "        ", 8);
}

void formatFlash() {
    LittleFS.format();
}


