#pragma once

#include <cstdint>

// ── USB MIDI interface (native ESP32-S3 USB OTG port via TinyUSB) ─────────────
//
// The ESP32-S3's built-in USB controller enumerates as a class-compliant USB
// MIDI device.  No driver is needed on macOS/Linux; Windows 10+ includes one.
//
// Flashing note: the native USB port is occupied by MIDI while running.
// Always flash via the UART port (the other USB connector on the DevKitC-1).

// Call once in setup(), before USB.begin().
void setupUsbMidi();

// Poll for incoming USB MIDI packets.  Call every iteration of loop().
void loopUsbMidi();

// ── Outgoing helpers ──────────────────────────────────────────────────────────
// All channel arguments are 1-based (1–16).

void usbMidiNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);
void usbMidiNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);
void usbMidiCC(uint8_t channel, uint8_t cc, uint8_t value);
void usbMidiProgramChange(uint8_t channel, uint8_t program);
void usbMidiPitchBend(uint8_t channel, int16_t value); // -8192 to +8191
