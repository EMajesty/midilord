#include "midiport.h"
#include "types.h"
#include <Arduino.h>
#include <MIDI.h>
#include <cstdint>

namespace {
const uint8_t RX1_PIN = 9;
const uint8_t TX1_PIN = 10;
const uint8_t TX2_PIN = 11;

HardwareSerial uart1 = HardwareSerial(1);
HardwareSerial uart2 = HardwareSerial(2);

MIDI_CREATE_INSTANCE(HardwareSerial, uart1, MIDI1);
MIDI_CREATE_INSTANCE(HardwareSerial, uart2, MIDI2);
} // namespace

namespace midiport {
void init() {
    uart1.begin(31250, SERIAL_8N1, RX1_PIN, TX1_PIN);
    uart2.begin(31250, SERIAL_8N1, -1, TX2_PIN);
    MIDI1.begin(MIDI_CHANNEL_OMNI);
    MIDI2.begin(MIDI_CHANNEL_OMNI);
}
void send(types::Event event) {
    switch (event.type) {
    case types::NONE:
        break;
    case types::INTERNAL:
        break;
    case types::CC:
        MIDI1.sendControlChange(event.message, event.value, event.channel);
        MIDI2.sendControlChange(event.message, event.value, event.channel);
        break;
    case types::PC:
        MIDI1.sendProgramChange(event.message, event.channel);
        MIDI2.sendProgramChange(event.message, event.channel);
        break;
    }
}
} // namespace midiport
