#include "usb_midi.h"

// TinyUSB MIDI is part of the ESP32 Arduino core — no extra lib_deps needed.
#include "USB.h"
#include "USBMIDI.h"

// One cable (port) is enough for a controller pedal.
// The global `USBMIDI` singleton is declared by the core; just call begin().

// ── Incoming stubs ────────────────────────────────────────────────────────────
// Replace these with real logic as the rest of the firmware grows.

static void onNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    (void)channel; (void)note; (void)velocity;
}

static void onNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
    (void)channel; (void)note; (void)velocity;
}

static void onCC(uint8_t channel, uint8_t cc, uint8_t value) {
    (void)channel; (void)cc; (void)value;
}

static void onProgramChange(uint8_t channel, uint8_t program) {
    (void)channel; (void)program;
}

// ── Setup / loop ─────────────────────────────────────────────────────────────

void setupUsbMidi() {
    // USBMIDI.begin() must come before USB.begin().
    USBMIDI.begin();
    USB.begin();
}

void loopUsbMidi() {
    midiEventPacket_t rx;
    while ((rx = USBMIDI.read()).header != 0) {
        uint8_t type    = rx.byte1 & 0xF0;
        uint8_t channel = (rx.byte1 & 0x0F) + 1; // convert 0-based to 1-based

        switch (type) {
            case 0x90: // Note On (velocity 0 == Note Off per MIDI spec)
                if (rx.byte3 > 0)
                    onNoteOn(channel, rx.byte2, rx.byte3);
                else
                    onNoteOff(channel, rx.byte2, 0);
                break;

            case 0x80: // Note Off
                onNoteOff(channel, rx.byte2, rx.byte3);
                break;

            case 0xB0: // Control Change
                onCC(channel, rx.byte2, rx.byte3);
                break;

            case 0xC0: // Program Change
                onProgramChange(channel, rx.byte2);
                break;

            default:
                break;
        }
    }
}

// ── Outgoing helpers ──────────────────────────────────────────────────────────

void usbMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
    USBMIDI.noteOn(note, velocity, channel);
}

void usbMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
    USBMIDI.noteOff(note, velocity, channel);
}

void usbMidiCC(uint8_t channel, uint8_t cc, uint8_t value) {
    USBMIDI.controlChange(cc, value, channel);
}

void usbMidiProgramChange(uint8_t channel, uint8_t program) {
    USBMIDI.programChange(program, channel);
}

void usbMidiPitchBend(uint8_t channel, int16_t value) {
    // MIDI pitch bend is 14-bit, centre = 0x2000.
    uint16_t raw = (uint16_t)(value + 8192);
    USBMIDI.pitchBend(raw, channel);
}
