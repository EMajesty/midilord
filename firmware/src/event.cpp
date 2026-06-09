#include "event.h"
#include "leds.h"
#include "midiport.h"
#include "storage.h"
#include "types.h"
#include <cstdint>

namespace {} // namespace

namespace event {
void init() {}
void trigger(uint8_t key) {
    types::Preset currPreset = storage::currBank.presets[key];
    leds::clear();
    leds::set(key, CRGB(currPreset.r, currPreset.g, currPreset.b));

    for (types::Event e : currPreset.events) {
        switch (e.type) {
        case types::NONE:
            break;
        case types::INTERNAL:
            break;
        case types::CC:
            midiport::sendCC(e.number, e.value, e.channel);
            break;
        case types::PC:
            midiport::sendPC(e.number, e.channel);
            break;
        }
    }
}
} // namespace event
