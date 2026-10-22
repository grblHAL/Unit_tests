#pragma once
#include "support/ioports_settings_host.h"
static inline void prepare_mpg_input_settings(uint8_t mpg_port, pull_mode_t neighbor_pull)
{
    CHECK(mpg_port < 2);
    engine_prepare();
    grbl.on_settings_changed = io_settings_changed;
    hal.driver_cap.mpg_mode = true;
    for(unsigned i = 0; i < 2; i++) {
        digital_pins[Port_Input][i].mode.input = true;
        digital_pins[Port_Input][i].mode.pull_mode = i == mpg_port ? PullMode_Down : neighbor_pull;
        digital_pins[Port_Input][i].mode.debounce = i == mpg_port;
        digital_pins[Port_Input][i].config = configure_input;
    }
    digital_pins[Port_Input][mpg_port].function = Input_MPGSelect;
    register_ioports();
    settings.ioport.invert_in.mask = 3;
    sys.ioinit_pending = true;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
}
