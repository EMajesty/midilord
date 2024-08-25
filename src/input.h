#pragma once

#include <Button2.h>
#include "lcd.h"
#include "midi-messaging.h"
#include "filesystem.h"

#define buttonPin1 2
#define buttonPin2 3
#define buttonPin3 4
#define buttonPin4 5
#define buttonPin5 6
#define buttonPin6 7
#define buttonPin7 8
#define buttonPin8 9

Button2 button1, button2, button3, button4, button5, button6, button7, button8;

void initInput();
void loopInput();
void buttonHandler(Button2& button);
void executeCommand(byte button);

void initInput() {
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
}

void loopInput() {
    button1.loop();
    button2.loop();
    button3.loop();
    button4.loop();
    button5.loop();
    button6.loop();
    button7.loop();
    button8.loop();
}

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
            sendBank(0);
            // serialMIDI.sendProgramChange(63, 15);
            break;
        case 2:
            serialMIDI.sendProgramChange(62, 15);
            break;
        case 3:
            serialMIDI.sendProgramChange(61, 15);
            break;
        case 4:
            serialMIDI.sendProgramChange(60, 15);
            break;
        case 5:
            demoData();
            // serialMIDI.sendProgramChange(59, 15);
            break;
        case 6:
            removeData();
            // serialMIDI.sendProgramChange(58, 15);
            break;
        case 7:
            writeFlash();
            // serialMIDI.sendProgramChange(57, 15);
            break;
        case 8:
            readFlash();
            // serialMIDI.sendProgramChange(56, 15);
            break;
    }
}
