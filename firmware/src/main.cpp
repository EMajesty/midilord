#include <Arduino.h>
#include "config.h"
#include "display.h"
#include "usb_midi.h"
#include "webserver.h"

// ── Forward declarations ─────────────────────────────────────────────────────
void setupMidi();
void setupFootswitches();

void loopMidi();
void loopFootswitches();

// ─────────────────────────────────────────────────────────────────────────────

void setup() {
    Serial.begin(115200);

    setupFootswitches();
    setupDisplay();
    setupUsbMidi(); // must be called before USB.begin() — handled inside
    setupMidi();
    setupWebServer();
}

void loop() {
    loopFootswitches();
    loopMidi();
    loopUsbMidi();
    loopDisplay();
    loopWebServer();
}

// ── Stubs (fill in per-module) ───────────────────────────────────────────────

void setupMidi() {}
void setupFootswitches() {
    for (int i = 0; i < FS_COUNT; i++) {
        pinMode(FS_PINS[i], INPUT_PULLUP);
    }
}

void loopMidi() {}
void loopFootswitches() {}
