#include "midiport.h"
#include <MIDI.h>

namespace {
HardwareSerial uart1 = HardwareSerial(1);
HardwareSerial uart2 = HardwareSerial(2);

// MIDI_CREATE_INSTANCE(HardwareSerial, uart1, MIDI1);
// MIDI_CREATE_INSTANCE(HardwareSerial, uart2, MIDI2);
} // namespace

namespace midiport {
void init() {
    // uart1.begin(21);
    // uart2.begin(47);
    //
    // MIDI1.begin();
    // MIDI2.begin();
}
void send(types::Event) {}
} // namespace midiport
