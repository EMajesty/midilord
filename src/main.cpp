#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Vector.h>
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
// MIDI_CREATE_DEFAULT_INSTANCE();
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

// ---------- LCD -------------------------------------------------------------
const byte rs = 16, enTop = 15, enBot= 14, d4 = 13, d5 = 12, d6 = 11, d7 = 10;

LiquidCrystal lcdTop(rs, enTop, d4, d5, d6, d7);
LiquidCrystal lcdBot(rs, enBot, d4, d5, d6, d7);

// ---------- Presets ---------------------------------------------------------
// bank[preset1, ..., preset8]
// preset[message, message, ...]
// message[type, channel, programnumber/controlnumber, controlvalue]
struct message {
    byte type;
    byte channel;
    byte number;
    byte value;
};

const byte ELEMENT_COUNT_MAX = 99;
message messageArray[ELEMENT_COUNT_MAX];

struct bank {
    Vector<message> preset(messageArray)[8];
};

bank banks[99];

enum MessageType {
    INTERNAL,
    CONTROL,
    PROGRAM
};

// ---------- Misc ------------------------------------------------------------
int bpm = 666;

// ---------- Function declarations -------------------------------------------
void drawHello();
void drawPresets();
void drawActivePreset(byte activePreset);
void drawBPM();
void drawClick();
void buttonHandler(Button2& button);
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

    button1.setPressedHandler(buttonHandler);
    button2.setPressedHandler(buttonHandler);
    button3.setPressedHandler(buttonHandler);
    button4.setPressedHandler(buttonHandler);
    button5.setPressedHandler(buttonHandler);
    button6.setPressedHandler(buttonHandler);
    button7.setPressedHandler(buttonHandler);
    button8.setPressedHandler(buttonHandler);

    MIDI.begin(MIDI_CHANNEL_OMNI);

    lcdTop.begin(40, 2);
    lcdBot.begin(40, 2);

    // drawHello();
    // delay(5000);
    // lcdTop.clear();
    // lcdBot.clear();
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
void buttonHandler(Button2& button) {
    executeCommand(button.getID());
    drawActivePreset(button.getID());
}

void executeCommand(byte button) {
    switch (bank[button])
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
    switch (button) {
        case 1:
            MIDI.sendProgramChange(63, 15);
            break;
        case 2:
            MIDI.sendProgramChange(62, 15);
            break;
        case 3:
            MIDI.sendProgramChange(61, 15);
            break;
        case 4:
            MIDI.sendProgramChange(60, 15);
            break;
        case 5:
            MIDI.sendProgramChange(59, 15);
            break;
        case 6:
            MIDI.sendProgramChange(58, 15);
            break;
        case 7:
            MIDI.sendProgramChange(57, 15);
            break;
        case 8:
            MIDI.sendProgramChange(56, 15);
            break;
    }

}
