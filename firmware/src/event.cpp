#include "event.h"
#include "leds.h"
#include "midiport.h"
#include "storage.h"
#include "types.h"
#include <cstdint>

namespace {} // namespace

namespace event {
void init() { types::Bank currBank = storage::getBank(); }
void trigger(uint8_t key) {
    types::Preset currPreset = currBank.presets[key];
    leds::setClear(key, currPreset.color);
    for (int i = 0;
         i < sizeof(currPreset.events) / sizeof(currPreset.events[0]); i++) {
        switch (currPreset.events[i].type) {
        case types::NONE:
            break;
        case types::INTERNAL:
            break;
        case types::CC:
            midiport::send(currPreset.events[i]);
            break;
        case types::PC:
            midiport::send(currPreset.events[i]);
            break;
        }
    }
}
void changeBank(uint8_t bank) {}
} // namespace event
