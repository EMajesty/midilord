#include "storage.h"
#include "types.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <LittleFS.h>
#include <cstdint>

namespace {
JsonDocument doc;
const uint8_t bankCount = 16;
uint8_t currBankIndex = 0;
} // namespace

namespace storage {
types::Bank currBank; // global data of current bank in memory
void init() {
    types::Bank initBank;
    doc["bank"] = initBank;

    LittleFS.begin(true);
    LittleFS.mkdir("/banks");
    for (int i = 0; i < bankCount; i++) {
        // check if files 0.json - 15.json exist (in case of bankCount = 16)
        // if a file does not exist, create one from types::Bank with default
        // values
        String path = "/banks/" + String(i) + ".json";
        if (!LittleFS.exists(path)) {
            File file = LittleFS.open(path, FILE_WRITE);
            serializeJson(doc, file);
        } else {
            Serial.println(path + " found");
        }
    }
    // getBank(currBankIndex);
}
void getBank(uint8_t bankIndex) {
    // String path = "/banks/" + String(bankIndex) + ".json";
    // File file = LittleFS.open(path, FILE_READ);
    // deserializeJson(doc, file);
    // currBank = doc["bank"];
    // currBankIndex = bankIndex;
    // // deserialize bank from filesystem to currBank
}
void nextBank() {
    if (currBankIndex < bankCount - 1) {
        getBank(currBankIndex + 1);
    }
}
void prevBank() {
    if (currBankIndex > 0) {
        getBank(currBankIndex - 1);
    }
}
void writeBank() {
    // Serial.println("Writing bank");
    // String path = "/banks/" + String(currBankIndex) + ".json";
    // File file = LittleFS.open(path, FILE_WRITE);
    // serializeJson(doc, currBank);
    // file.print(doc);
}
} // namespace storage
