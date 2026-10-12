#pragma once
#include "support/ioports_host.h"
static unsigned input_config_calls[2], output_config_calls[2];
static gpio_in_config_t captured_input[2];
static gpio_out_config_t captured_output[2];
static inline void io_settings_changed(settings_t *current, settings_changed_flags_t changed) { CHECK(current == &settings); (void)changed; }
static inline bool configure_input(xbar_t *pin, xbar_cfg_ptr_t data, bool persistent) { CHECK(pin->id < 2 && !persistent); captured_input[pin->id] = *data.gpio_in_config; input_config_calls[pin->id]++; return true; }
static inline bool configure_output(xbar_t *pin, xbar_cfg_ptr_t data, bool persistent) { CHECK(pin->id < 2 && !persistent); captured_output[pin->id] = *data.gpio_out_config; output_config_calls[pin->id]++; return true; }
static inline void prepare_io_settings(void)
{
    engine_prepare();
    grbl.on_settings_changed = io_settings_changed;
    for(unsigned i = 0; i < 2; i++) {
        digital_pins[Port_Input][i].mode.input = true;
        digital_pins[Port_Input][i].mode.pull_mode = PullMode_Up;
        digital_pins[Port_Input][i].config = configure_input;
        digital_pins[Port_Output][i].mode.output = true;
        digital_pins[Port_Output][i].config = configure_output;
    }
    register_ioports();
}
static inline status_code_t store_io_setting(setting_id_t id, const char *value) { char text[16]; CHECK(strlen(value) < sizeof(text)); strcpy(text, value); return settings_store_setting(id, text); }
