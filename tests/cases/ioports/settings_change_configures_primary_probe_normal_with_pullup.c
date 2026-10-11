#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][0].function = Input_Probe;
    digital_pins[Port_Input][0].mode.debounce = true;
    settings.probe.invert_probe_pin = false;
    settings.probe.disable_probe_pullup = false;
    settings.ioport.invert_in.mask = 1;
    ioport_setting_changed(Setting_InvertProbePin);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 0);
    CHECK(captured_input[0].inverted == false);
    CHECK(captured_input[0].pull_mode == PullMode_Up);
    CHECK(!captured_input[0].debounce);
    CHECK((settings.ioport.invert_in.mask & 1) == 0);
    return EXIT_SUCCESS;
}
