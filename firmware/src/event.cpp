#include "event.h"
#include "HardwareSerial.h"
#include "leds.h"
#include "serialMIDI.h"
#include <MIDI.h>
#include <cstdint>

namespace {
enum EventType { NONE, INTERNAL, CC, PC };
enum Output { ALL, M1, M2, M3, M4 };
struct Event {
    EventType type;
    uint8_t message;
    uint8_t value;
    uint8_t channel;
    Output output = ALL;
};
struct Preset {
    char name[6];
    Event events[16];
    CRGB color = CRGB(128, 128, 0);
};
struct Bank {
    Preset presets[8];
};
struct Memory {
    Bank banks[16];
};

Memory mem;
uint8_t currBank = 0;

HardwareSerial uart1 = HardwareSerial(1);
HardwareSerial uart2 = HardwareSerial(2);
HardwareSerial uart3 = HardwareSerial(3);
HardwareSerial uart4 = HardwareSerial(4);

MIDI_CREATE_INSTANCE(HardwareSerial, uart1, MIDI1);
MIDI_CREATE_INSTANCE(HardwareSerial, uart2, MIDI2);
MIDI_CREATE_INSTANCE(HardwareSerial, uart3, MIDI3);
MIDI_CREATE_INSTANCE(HardwareSerial, uart4, MIDI4);
} // namespace

namespace event {
void init() {
    uart1.begin(21);
    uart2.begin(47);
    uart3.begin(48);
    uart4.begin(45);

    MIDI1.begin();
    MIDI2.begin();
    MIDI3.begin();
    MIDI4.begin();
}
void trigger(uint8_t key) {
    Preset currPreset = mem.banks[currBank].presets[key];
    leds::setClear(key, currPreset.color);
    for (int i = 0;
         i < sizeof(currPreset.events) / sizeof(currPreset.events[0]); i++) {
        switch (currPreset.events[i].type) {
        case NONE:
            break;
        case INTERNAL:
            break;
        case CC:
            MIDI.sendControlChange(currPreset.events[i].message,
                                   currPreset.events[i].value,
                                   currPreset.events[i].channel);
            break;
        case PC:
            MIDI.sendProgramChange(currPreset.events[i].value,
                                   currPreset.events[i].channel);
            break;
        }
    }
}
} // namespace event
