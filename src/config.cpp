#include "config.h"
#include <cstring>

Config config;

void demoData() {
    strncpy(config.banks[0].name, "teppo", 8);
    strncpy(config.banks[0].presets[0].name, "kurkku", 8);
    strncpy(config.banks[0].presets[1].name, "mopo", 8);
    strncpy(config.banks[0].presets[2].name, "a", 8);
    strncpy(config.banks[0].presets[3].name, "12345678", 8);
    strncpy(config.banks[0].presets[4].name, "juusto", 8);
    strncpy(config.banks[0].presets[5].name, "bumtsi", 8);
    strncpy(config.banks[0].presets[6].name, "bum", 8);
    strncpy(config.banks[0].presets[7].name, "kebab", 8);

    config.banks[0].presets[0].messages[0].type = CONTROL;
    config.banks[0].presets[0].messages[0].number = 1;
    config.banks[0].presets[0].messages[0].value = 42;
    config.banks[0].presets[0].messages[0].channel = 1;

    config.banks[0].presets[1].messages[0].type = PROGRAM;
    config.banks[0].presets[1].messages[0].number = 66;
    config.banks[0].presets[1].messages[0].channel = 1;

    config.banks[0].presets[2].messages[0].type = CONTROL;
    config.banks[0].presets[2].messages[0].number = 2;
    config.banks[0].presets[2].messages[0].value = 55;
    config.banks[0].presets[2].messages[0].channel = 1;

    config.banks[0].presets[3].messages[0].type = PROGRAM;
    config.banks[0].presets[3].messages[0].number = 77;
    config.banks[0].presets[3].messages[0].channel = 1;

    config.banks[0].presets[4].messages[0].type = CONTROL;
    config.banks[0].presets[4].messages[0].number = 1;
    config.banks[0].presets[4].messages[0].value = 42;
    config.banks[0].presets[4].messages[0].channel = 1;

    config.banks[0].presets[5].messages[0].type = PROGRAM;
    config.banks[0].presets[5].messages[0].number = 66;
    config.banks[0].presets[5].messages[0].channel = 1;

    config.banks[0].presets[6].messages[0].type = CONTROL;
    config.banks[0].presets[6].messages[0].number = 2;
    config.banks[0].presets[6].messages[0].value = 55;
    config.banks[0].presets[6].messages[0].channel = 1;

    config.banks[0].presets[7].messages[0].type = PROGRAM;
    config.banks[0].presets[7].messages[0].number = 77;
    config.banks[0].presets[7].messages[0].channel = 1;
}

