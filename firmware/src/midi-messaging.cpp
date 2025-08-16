#include "midi-messaging.h"
#include <MIDI.h>
#include <Adafruit_TinyUSB.h>
#include "config.h"

Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, serialMIDI);
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, usbMIDI);

byte signatureArray[6] = {0xF0, 0x7D, 0x6D, 0x64, 0x6C};


void initMidi() {
    // while (!TinyUSBDevice.mounted())
    // {
    //     delay(1);
    // }
 
    usbMIDI.begin(MIDI_CHANNEL_OMNI);
    usbMIDI.setHandleSystemExclusive(handleSystemExclusive);

    serialMIDI.begin(MIDI_CHANNEL_OMNI);
    serialMIDI.setHandleSystemExclusive(handleSystemExclusive);
}

void loopMidi() {
    if (TinyUSBDevice.mounted()) {
        usbMIDI.read();
    }

    serialMIDI.read();
}

void presetToByteArray(byte preset, byte presetArray[], int size) {
    Preset& ref = config.banks[config.currentBank].presets[preset];

    memcpy(presetArray, ref.name, strlen(ref.name));

    for (int i = 0; i < MESSAGES_MAX; i++) {
        for (int j = 0; j < 4; j++) { // Four fields in the Message struct
            byte val;
            switch (j) {
                case 0:
                    val = ref.messages[i].type;
                    break;
                case 1:
                    val = ref.messages[i].channel;
                    break;
                case 2:
                    val = ref.messages[i].number;
                    break;
                case 3:
                    val = ref.messages[i].value;
                    break;
            }
            presetArray[8 + i * 4 + j] = val;
        }
    }
}

void sendBank(byte bank) {
    // int i = 0;
    for (byte i = 0; i < 8; i++) {
        byte presetArray[12 * MESSAGES_MAX] = {0};
        presetToByteArray(i, presetArray, 12 * MESSAGES_MAX);

        byte startArray[6] = {0xF0, 0x7D, 0x6D, 0x64, 0x6C, 0x01};
        byte checkSumArray[sizeof(startArray) + sizeof(presetArray)];

        memcpy(checkSumArray, startArray, sizeof(startArray));
        memcpy(checkSumArray + sizeof(startArray), presetArray, sizeof(presetArray));

        byte checkSum = calculateChecksum(sizeof(checkSumArray), checkSumArray);
        byte endArray[2] = {checkSum, 0xF7};

        byte outputArray[sizeof(checkSumArray) + sizeof(endArray)];
        memcpy(outputArray, checkSumArray, sizeof(checkSumArray));
        memcpy(outputArray + sizeof(checkSumArray), endArray, sizeof(endArray));

        usbMIDI.sendSysEx(sizeof(outputArray), outputArray, true);
    }
}

void handleSystemExclusive(byte* array, unsigned size) {
    if (memcmp(array, signatureArray, sizeof(signatureArray)) == 0) {
        switch (array[5]) { // Byte: Ack
            case 0x00: // Checksum ok, proceed
                switch (array[6]) { // Byte: Instructions
                    case 0x00: // No instruction
                        break;
                    case 0x01: // Send current bank
                        sendBank(config.currentBank);
                        break;
                    // case 0x10: // Bank up
                    //     if (config.currentBank < BANKS_MAX) {
                    //         config.currentBank++;
                    //     }
                    //     break;
                    // case 0x11: // Bank down
                    //     if (config.currentBank > 0) {
                    //         config.currentBank--;
                    //     }
                    //     break;
                    // case 0x12: // Goto bank
                    //     if (array[7] <= 30 && array[7] >= 0) {
                    //         config.currentBank = array[7];
                    //     }
                    //     break;
                    default:
                        break;
                }
            case 0x01: // Checksum mismatch, resend last
                break;
            default:
                break;
        }
    }
}

byte calculateChecksum(int len, byte *ptr) {
    byte checkSum = *(ptr);

    for (int i = 1; i < len; i++) {
        checkSum ^= *(ptr + i);
    }

    checkSum &= 0x7F;
    return checkSum;
}

void executeCommand(byte presetNum) {
    Message* ref = config.banks[config.currentBank].presets[presetNum].messages;

    for (int i = 0; i < MESSAGES_MAX; i++) {
        switch (ref[i].type) {
            case INTERNAL:
                break;
            case CONTROL:
                serialMIDI.sendControlChange(ref[i].number, ref[i].value, ref[i].channel);
                break;
            case PROGRAM:
                serialMIDI.sendProgramChange(ref[i].value, ref[i].channel);
                break;
        }
    }
}
