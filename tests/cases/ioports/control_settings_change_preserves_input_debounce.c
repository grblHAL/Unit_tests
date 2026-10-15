#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][0].function = Input_FeedHold;
    digital_pins[Port_Input][0].mode.debounce = true;
    settings.control_invert.feed_hold = true;
    settings.control_disable_pullup.feed_hold = true;
    ioport_setting_changed(Setting_ControlInvertMask);
    CHECK(input_config_calls[0] == 1);
    CHECK(captured_input[0].inverted);
    CHECK(captured_input[0].pull_mode == PullMode_Down);
    CHECK(captured_input[0].debounce);
    CHECK((settings.ioport.invert_in.mask & 1) == 1);
    return EXIT_SUCCESS;
}
