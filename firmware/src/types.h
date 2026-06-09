#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <cstdint>
#include <cstring>

namespace types {
enum EventType { NONE, INTERNAL, CC, PC };
struct Event {
    EventType type;
    uint8_t number;
    uint8_t value;
    uint8_t channel;
};
struct Preset {
    char name[7]; // 6 characters + null terminator
    Event events[16];
    uint8_t r = 128, g = 0, b = 0;
};
struct Bank {
    char name[9]; // 8 characters + null terminator
    Preset presets[8];
};

inline void convertToJson(const types::Event &e, JsonVariant var) {
    var["type"] = e.type;
    var["number"] = e.number;
    var["value"] = e.value;
    var["channel"] = e.channel;
}
inline void convertFromJson(JsonVariantConst src, types::Event &e) {
    e.type = src["type"];
    e.number = src["number"];
    e.value = src["value"];
    e.channel = src["channel"];
}
inline void convertToJson(const types::Preset &p, JsonVariant var) {
    var["name"] = p.name;
    JsonArray events = var["events"].to<JsonArray>();
    for (const types::Event &e : p.events) {
        events.add(e);
    }
    var["r"] = p.r;
    var["g"] = p.g;
    var["b"] = p.b;
}
inline void convertFromJson(JsonVariantConst src, types::Preset &p) {
    strlcpy(p.name, src["name"], sizeof(p.name));
    JsonArrayConst e = src["events"];
    for (size_t i = 0; i < e.size(); i++) {
        p.events[i] = e[i];
    }
    p.r = src["r"];
    p.g = src["g"];
    p.b = src["b"];
}
inline void convertToJson(const types::Bank &b, JsonVariant var) {
    var["name"] = b.name;
    JsonArray presets = var["presets"].to<JsonArray>();
    for (const types::Preset &p : b.presets) {
        presets.add(p);
    }
}
inline void convertFromJson(JsonVariantConst src, types::Bank &b) {
    strlcpy(b.name, src["name"], sizeof(b.name));
    JsonArrayConst p = src["presets"];
    for (size_t i = 0; i < p.size(); i++) {
        b.presets[i] = p[i];
    }
}
} // namespace types
