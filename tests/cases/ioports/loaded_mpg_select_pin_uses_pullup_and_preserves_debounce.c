#include "support/ioports_settings_host.h"
int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][0].function = Input_MPGSelect;
    digital_pins[Port_Input][0].mode.pull_mode = PullMode_Down;
    digital_pins[Port_Input][0].mode.debounce = true;
    settings.ioport.invert_in.mask = 3;
    sys.ioinit_pending = true;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    CHECK(captured_input[0].pull_mode == PullMode_Up);
    CHECK(captured_input[0].debounce && !captured_input[0].inverted);
    CHECK(captured_input[1].inverted);
    return EXIT_SUCCESS;
}
