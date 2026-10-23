#pragma once
#include "support/ioports_analog_host.h"
#include "spindle_control.h"
#include "nvs_buffer.h"
static spindle1_pwm_settings_t *secondary_pwm_settings;
static setting_details_t *secondary_pwm_owner;
static unsigned secondary_pwm_changes, primary_pwm_changes;
static bool secondary_pwm_no_change_callback;
static void secondary_pwm_changed(spindle1_pwm_settings_t *current)
{
    CHECK(current == secondary_pwm_settings);
    secondary_pwm_changes++;
}
static void primary_pwm_changed(settings_t *current, settings_changed_flags_t changed)
{
    CHECK(current == &settings);
    (void)changed;
    primary_pwm_changes++;
}
static inline void prepare_secondary_pwm_settings_with_cap(bool ports, spindle_cap_t cap)
{
    if(ports) {
        prepare_analog_ports();
        register_ioports();
        analog_pins[Port_Output][0].cap.pwm = true;
        analog_pins[Port_Output][1].cap.pwm = true;
    } else
        engine_prepare();
    hal.nvs.type = NVS_EEPROM;
    secondary_pwm_settings = spindle1_settings_add(ports);
    CHECK(secondary_pwm_settings != NULL);
    grbl.on_settings_changed = primary_pwm_changed;
    spindle1_settings_register(cap, secondary_pwm_no_change_callback ? NULL : secondary_pwm_changed);
    CHECK(setting_get_details(Setting_SpindleInvertMask1, &secondary_pwm_owner) != NULL);
    CHECK(secondary_pwm_owner != NULL);
    secondary_pwm_owner->restore();
    secondary_pwm_owner->load();
}
static inline status_code_t secondary_pwm_store(setting_id_t id, const char *value)
{
    char text[64];
    CHECK(strlen(value) < sizeof(text));
    strcpy(text, value);
    return settings_store_setting(id, text);
}

static inline void prepare_secondary_pwm_settings(bool ports)
{
    prepare_secondary_pwm_settings_with_cap(ports, (spindle_cap_t){.variable = true, .direction = true, .pwm_invert = true});
}
