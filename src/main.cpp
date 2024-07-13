#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
// #include <vector>
#include <MIDI.h>
#include <Button2.h>


// ---------- Defines ---------------------------------------------------------
#define buttonPin1 2
#define buttonPin2 3
#define buttonPin3 4
#define buttonPin4 5
#define buttonPin5 6
#define buttonPin6 7
#define buttonPin7 8
#define buttonPin8 9

// ---------- File system -----------------------------------------------------


// ---------- Input -----------------------------------------------------------
Button2 button1, button2, button3, button4, button5, button6, button7, button8;

// ---------- MIDI ------------------------------------------------------------
MIDI_CREATE_DEFAULT_INSTANCE();

// ---------- LCD -------------------------------------------------------------
const byte rs = 16, enTop = 15, enBot= 14, d4 = 13, d5 = 12, d6 = 11, d7 = 10;

LiquidCrystal lcdTop(rs, enTop, d4, d5, d6, d7);
LiquidCrystal lcdBot(rs, enBot, d4, d5, d6, d7);

// ---------- Misc ------------------------------------------------------------
bool summoningSickness = true;
byte currentBank[8][4];
// std::vector<byte> currentBank;
int bpm = 666;

enum MessageType {
    INTERNAL,
    CONTROL,
    PROGRAM
};

// ---------- Function declarations -------------------------------------------
void drawHello();
void drawPresets();
void drawActivePreset(byte activePreset);
void drawBPM();
void drawClick();
void clickHandler(Button2& button);
void executeCommand(byte command);


// ---------- Actual shit -----------------------------------------------------
void setup() {

    button1.begin(buttonPin1);
    button2.begin(buttonPin2);
    button3.begin(buttonPin3);
    button4.begin(buttonPin4);
    button5.begin(buttonPin5);
    button6.begin(buttonPin6);
    button7.begin(buttonPin7);
    button8.begin(buttonPin8);

    button1.setID(1);
    button2.setID(2);
    button3.setID(3);
    button4.setID(4);
    button5.setID(5);
    button6.setID(6);
    button7.setID(7);
    button8.setID(8);

    button1.setPressedHandler(clickHandler);
    button2.setPressedHandler(clickHandler);
    button3.setPressedHandler(clickHandler);
    button4.setPressedHandler(clickHandler);
    button5.setPressedHandler(clickHandler);
    button6.setPressedHandler(clickHandler);
    button7.setPressedHandler(clickHandler);
    button8.setPressedHandler(clickHandler);

    MIDI.begin(MIDI_CHANNEL_OMNI);

    lcdTop.begin(40, 2);
    lcdBot.begin(40, 2);

    // drawHello();
    // delay(5000);
    // lcdTop.clear();
    // lcdBot.clear();
    //
    //
    // summoningSickness = false;
    drawPresets();
}

void loop() {
    drawBPM();
 
    // for (byte i = 1; i < 9; i++) {
    //     drawActivePreset(i);
    //     delay(1000);
    // }
    button1.loop();
    button2.loop();
    button3.loop();
    button4.loop();
    button5.loop();
    button6.loop();
    button7.loop();
    button8.loop();

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
void clickHandler(Button2& button) {
    // lcdTop.setCursor(0, 0);
    // lcdTop.print("button");

    drawActivePreset(button.getID());
    // switch (button.getType()) {
    //     case single_click:
    //         // executeCommand(button.getID());
    //         // lcdTop.setCursor(0, 1);
    //         // lcdTop.print(button.getID());
    //         break;
    //     case long_click:
    //         break;
    //     case double_click:
    //         break;
    //     case triple_click:
    //         break;
    //     case empty:
    //         break;
    // }
}

void executeCommand(byte button) {
    // for (const auto& command : currentBank[button]) {
    //     switch (command) {
    //         case INTERNAL:
    //             break;
    //         case CONTROL:
    //             break;
    //         case PROGRAM:
    //             break;
    //     }
    // }
}
