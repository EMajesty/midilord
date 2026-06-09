#include "midiport.h"
#include <Arduino.h>
#include <MIDI.h>
#include <cstdint>

namespace {
const uint8_t RX_PIN = 9;
const uint8_t TX_PIN = 10;

HardwareSerial uart = HardwareSerial(1);

MIDI_CREATE_INSTANCE(HardwareSerial, uart, MIDI);
} // namespace

namespace midiport {
void init() {
    uart.begin(31250, SERIAL_8N1, RX_PIN, TX_PIN);
    MIDI.begin(MIDI_CHANNEL_OMNI);
}
void sendCC(uint8_t number, uint8_t value, uint8_t channel) {
    MIDI.sendControlChange(number, value, channel);
}
void sendPC(uint8_t number, uint8_t channel) {
    MIDI.sendProgramChange(number, channel);
}
} // namespace midiport
