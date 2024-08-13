#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <MIDI.h>
#include <Button2.h>
#include <LittleFileSystem2.h>
#include <BlockDevice.h>
#include <cstdio>

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
mbed::BlockDevice *bd = mbed::BlockDevice::get_default_instance();
mbed::LittleFileSystem2 fs("fs", bd);

const char *configPath = "/fs/config";

// ---------- Input -----------------------------------------------------------
Button2 button1, button2, button3, button4, button5, button6, button7, button8;

// ---------- MIDI ------------------------------------------------------------
// MIDI_CREATE_DEFAULT_INSTANCE();
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
// USBMidi usbMidi;

// ---------- LCD -------------------------------------------------------------
const byte rs = 16, enTop = 15, enBot= 14, d4 = 13, d5 = 12, d6 = 11, d7 = 10;

LiquidCrystal lcdTop(rs, enTop, d4, d5, d6, d7);
LiquidCrystal lcdBot(rs, enBot, d4, d5, d6, d7);

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
    char *name;
    Message messages[30];
};

struct Bank {
    Preset presets[8];
};

struct Config {
    Bank banks[30];
    byte currentBank = 0;
    byte currentPreset;
    int bpm;
} config;

enum MessageType {
    INTERNAL,
    CONTROL,
    PROGRAM
};


// ---------- Function declarations -------------------------------------------
void drawHello();
void drawPresets();
void drawActivePreset(byte activePreset);
void drawCurrentBank();
void drawBPM();
void drawClick();
void buttonHandler(Button2& button);
void executeCommand(byte command);
void readFlash();
void writeFlash();
void demoData();
void removeData();
void sendBank(byte bank);
void parseSysex();
byte calculateChecksum(int len, byte *ptr);

// ---------- Actual shit -----------------------------------------------------
void setup() {
    bd->init();
    int err = fs.mount(bd);

    if (err) {
        mbed::LittleFileSystem2::format(bd);
        fs.mount(bd);
    }

    readFlash();

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

    button1.loop();
    button2.loop();
    button3.loop();
    button4.loop();
    button5.loop();
    button6.loop();
    button7.loop();
    button8.loop();

    // MIDI.read();
}

// ---------- MIDI Functions --------------------------------------------------
void sendBank(byte bank) {
    byte bankArray[sizeof(config.banks[bank])];
    memcpy(bankArray, &config.banks[bank], sizeof(bankArray));

    byte startArray[6] = {0xF0, 0x7D, 0x6D, 0x64, 0x6C, 0x00};

    byte checkSumArray[sizeof(startArray) + sizeof(bankArray)];
    memcpy(checkSumArray, startArray, sizeof(startArray));
    memcpy(checkSumArray + sizeof(startArray), bankArray, sizeof(bankArray));

    byte checkSum = calculateChecksum(sizeof(checkSumArray), checkSumArray);
    byte endArray[2] = {checkSum, 0xF7};

    byte outputArray[sizeof(checkSumArray) + sizeof(endArray)];
    memcpy(outputArray, checkSumArray, sizeof(checkSumArray));
    memcpy(outputArray + sizeof(checkSumArray), endArray, sizeof(endArray));

    // MIDI.sendSysEx(sizeof(outputArray), outputArray, true);
}

void parseSysex() {
}

byte calculateChecksum(int len, byte *ptr) {
    byte checkSum = *(ptr);

    for (int i = 1; i < len; i++) {
        checkSum ^= *(ptr + i);
    }

    checkSum &= 0x7F;
    return checkSum;
}

// ---------- Filesystem Functions --------------------------------------------
void readFlash() {
    byte byteArray[sizeof(Config)];
    
    FILE *fp = fopen(configPath, "rb");
    fread(byteArray, sizeof(byteArray), 1, fp);
    fclose(fp);

    memcpy(&config, byteArray, sizeof(Config));
}

void writeFlash() {
    FILE *fp = fopen(configPath, "wb");
    fwrite(&config, sizeof(Config), 1, fp);
    fclose(fp);
}

void demoData() {
    // config.banks[0].presets[0].name = "kurkku";
    // config.banks[0].presets[1].name = "mopo";
    // config.banks[0].presets[2].name = "a";
    // config.banks[0].presets[3].name = "12345678";
}

void removeData() {
    // config.banks[0].presets[0].name = "        ";
    // config.banks[0].presets[1].name = "        ";
    // config.banks[0].presets[2].name = "        ";
    // config.banks[0].presets[3].name = "        ";
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
    lcdTop.print(config.banks[config.currentBank].presets[0].name);
    lcdTop.setCursor(11, 0);
    lcdTop.print(config.banks[config.currentBank].presets[1].name);
    lcdTop.setCursor(21, 0);
    lcdTop.print(config.banks[config.currentBank].presets[2].name);
    lcdTop.setCursor(31, 0);
    lcdTop.print(config.banks[config.currentBank].presets[3].name);
    lcdBot.setCursor(1, 1);
    lcdTop.print(config.banks[config.currentBank].presets[4].name);
    lcdBot.setCursor(11, 1);
    lcdTop.print(config.banks[config.currentBank].presets[5].name);
    lcdBot.setCursor(21, 1);
    lcdTop.print(config.banks[config.currentBank].presets[6].name);
    lcdBot.setCursor(31, 1);
    lcdTop.print(config.banks[config.currentBank].presets[7].name);
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

void drawCurrentBank() {
    lcdTop.setCursor(30, 1);
    lcdTop.print("Bank: ");
    lcdTop.print(config.currentBank);
}

void drawBPM() {
    lcdTop.setCursor(0, 1);
    lcdTop.print("BPM: ");
    lcdTop.print(config.bpm);
}

void drawClick() {
}

// ---------- Input Functions -------------------------------------------------
void buttonHandler(Button2& button) {
    executeCommand(button.getID());
    drawActivePreset(button.getID());
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
