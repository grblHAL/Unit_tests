#pragma once
#include "support/engine_host.h"
#include "check.h"
#include <string.h>
static unsigned change_callbacks;
static void changed_settings(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    (void)changed;
    change_callbacks++;
}
static inline void prepare_settings_store(void)
{
    engine_parser_prepare();
    grbl.on_settings_changed = changed_settings;
}
static inline status_code_t store_setting(setting_id_t id, const char *value)
{
    char text[64];
    CHECK(strlen(value) < sizeof(text));
    strcpy(text, value);
    return settings_store_setting(id, text);
}
