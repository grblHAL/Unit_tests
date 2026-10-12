#pragma once
#include "support/delta_host.h"
#include "protocol.h"
#include <string.h>
static unsigned delta_option_calls, delta_realtime_calls, delta_unit_calls, delta_description_calls;
static bool delta_option_new;
static unsigned delta_homing_calls;
static bool delta_homing_success;
static axes_signals_t delta_homing_axes;
static bool delta_connected(void) { return true; }
static control_signals_t delta_controls(void) { return (control_signals_t){0}; }
static void delta_homing_previous(axes_signals_t cycle, bool success)
{ delta_homing_calls++; delta_homing_axes = cycle; delta_homing_success = success; }
static void delta_options_previous(bool newopt) { delta_option_calls++; delta_option_new = newopt; }
static void delta_realtime_previous(stream_write_ptr write, report_tracking_flags_t flags)
{
    (void)flags; delta_realtime_calls++; write("|Fixture:1");
}
static const char *delta_units_previous(setting_id_t id, uint_fast8_t axis)
{
    (void)id; (void)axis; delta_unit_calls++; return "fixture-unit";
}
static const char *delta_description_previous(setting_id_t id)
{
    (void)id; delta_description_calls++; return "fixture description";
}
static void delta_configure_callbacks(void)
{
    limits_init();
    hal.stream.is_connected = delta_connected;
    hal.control.get_state = delta_controls;
    grbl.on_homing_completed = delta_homing_previous;
    grbl.on_report_options = delta_options_previous;
    grbl.on_realtime_report = delta_realtime_previous;
    grbl.on_set_axis_setting_unit = delta_units_previous;
    grbl.on_setting_get_description = delta_description_previous;
    grbl.on_execute_realtime = protocol_execute_noop;
}
static inline void prepare_delta_api(void) { prepare_delta_with_callbacks(delta_configure_callbacks); }
static inline setting_details_t *delta_details(void)
{
    setting_details_t *details = NULL;
    CHECK(setting_get_details(Setting_Kinematics0, &details) != NULL);
    CHECK(details != NULL); return details;
}
static inline status_code_t delta_store(setting_id_t id, const char *value)
{
    char text[32]; CHECK(strlen(value) < sizeof(text)); strcpy(text, value);
    return settings_store_setting(id, text);
}
