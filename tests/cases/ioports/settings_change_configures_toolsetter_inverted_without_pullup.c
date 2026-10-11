#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][0].function = Input_Toolsetter;
    digital_pins[Port_Input][0].mode.debounce = true;
    settings.probe.invert_toolsetter_input = true;
    settings.probe.disable_toolsetter_pullup = true;
    settings.ioport.invert_in.mask = 0;
    ioport_setting_changed(Setting_InvertProbePin);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 0);
    CHECK(captured_input[0].inverted == true);
    CHECK(captured_input[0].pull_mode == PullMode_None);
    CHECK(!captured_input[0].debounce);
    CHECK((settings.ioport.invert_in.mask & 1) == 1);
    return EXIT_SUCCESS;
}
