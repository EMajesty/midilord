#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
// #include <vector>
#include <MIDI.h>

// ---------- MIDI ------------------------------------------------------------
MIDI_CREATE_DEFAULT_INSTANCE();

// ---------- LCD -------------------------------------------------------------
// const byte rs = 6, enTop = 4, enBot= 5, d4 = 0, d5 = 1, d6 = 2, d7 = 3;
const byte rs = 16, enTop = 15, enBot= 14, d4 = 13, d5 = 12, d6 = 11, d7 = 10;

LiquidCrystal lcdTop(rs, enTop, d4, d5, d6, d7);
LiquidCrystal lcdBot(rs, enBot, d4, d5, d6, d7);

// ---------- Keypad ----------------------------------------------------------
const byte ROWS = 2;
const byte COLS = 4;

char keys[ROWS][COLS] {
    {'1', '2', '3', '4'},
    {'5', '6', '7', '8'}
};

byte rowPins[ROWS] = {7, 8};
byte colPins[COLS] = {9, 10, 11, 12};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ---------- Misc ------------------------------------------------------------
bool summoningSickness = true;
byte currentBank[8][4];
// std::vector<byte> currentBank;
int bpm = 666;

// ---------- Function declarations -------------------------------------------
void drawHello();
void drawPresets();
void drawActivePreset(byte activePreset);
void drawBPM();
void drawClick();
void keypadEvent(KeypadEvent key);
void executeCommand(byte command);


// ---------- Actual shit -----------------------------------------------------
void setup() {
    MIDI.begin(MIDI_CHANNEL_OMNI);

    lcdTop.begin(40, 2);
    lcdBot.begin(40, 2);

    keypad.addEventListener(keypadEvent);

    drawHello();
    delay(5000);
    lcdTop.clear();
    lcdBot.clear();


    summoningSickness = false;
}

void loop() {
    // if (millis() > 5000 && summoningSickness) {
    //     lcdTop.clear();
    //     lcdBot.clear();
    //
    //     summoningSickness = false;
    //     drawPresets();
    //     drawBPM();
    // }



    drawPresets();
    drawBPM();
 
    for (byte i = 1; i < 9; i++) {
        drawActivePreset(i);
        delay(1000);
    }

    MIDI.read();
}


// ---------- LCD Functions ---------------------------------------------------
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
    lcdTop.print("Preset 1");
    lcdTop.setCursor(11, 0);
    lcdTop.print("Preset 2");
    lcdTop.setCursor(21, 0);
    lcdTop.print("Preset 3");
    lcdTop.setCursor(31, 0);
    lcdTop.print("Preset 4");
    lcdBot.setCursor(1, 1);
    lcdBot.print("Preset 5");
    lcdBot.setCursor(11, 1);
    lcdBot.print("Preset 6");
    lcdBot.setCursor(21, 1);
    lcdBot.print("Preset 7");
    lcdBot.setCursor(31, 1);
    lcdBot.print("Preset 8");
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

void drawBPM() {
    lcdTop.setCursor(0, 1);
    lcdTop.print("BPM: ");
    lcdTop.print(bpm);
}

void drawClick() {
}

// ---------- Input Functions -------------------------------------------------
void keypadEvent(KeypadEvent key) {
    switch (keypad.getState()) {
        case PRESSED:
            executeCommand(key);
            break;
        case RELEASED:
            break;
        case HOLD:
            break;
        case IDLE:
            break;
    }
}

void executeCommand(byte key) {
    for (const auto& command : currentBank[key]) {
        switch (command) {
        
        }
    }
}
