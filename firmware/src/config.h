#pragma once

// ── Footswitches ────────────────────────────────────────────────────────────
constexpr int FS_COUNT = 8;
constexpr int FS_PINS[FS_COUNT] = {1, 2, 3, 4, 5, 6, 7, 8};

// ── LCD (HD44780, 4-bit parallel) ────────────────────────────────────────────
// 4x40 is two 4x20 controllers sharing the same bus with separate EN lines.
constexpr int LCD_RS = 15;
constexpr int LCD_EN1 = 16; // enable for columns 1-20
constexpr int LCD_EN2 = 17; // enable for columns 21-40
constexpr int LCD_D4 = 18;
constexpr int LCD_D5 = 19;
constexpr int LCD_D6 = 20;
constexpr int LCD_D7 = 21;

// ── MIDI ─────────────────────────────────────────────────────────────────────
// UART0 reserved for debug; use UART1 for MIDI IN, UART2 for MIDI OUT
constexpr int MIDI_IN_RX = 44;
constexpr int MIDI_OUT_TX = 43;
// If additional independent MIDI outs are needed, assign more UART TX pins
// here.

// ── Power ────────────────────────────────────────────────────────────────────
// 9 V in → regulated 3.3 V for ESP32-S3 logic. No pin config needed here.

// ── Tap Tempo ────────────────────────────────────────────────────────────────
// Tap tempo is handled by one of the footswitches (configured per-preset).

// ── WiFi ─────────────────────────────────────────────────────────────────────
// Update these before flashing.
constexpr const char *WIFI_SSID = "midilord";
constexpr const char *WIFI_PASSWORD = "midilord";

// ── Presets / Banks ──────────────────────────────────────────────────────────
constexpr int BANK_COUNT = 16;
constexpr int PRESET_COUNT = 8; // one per footswitch per bank
