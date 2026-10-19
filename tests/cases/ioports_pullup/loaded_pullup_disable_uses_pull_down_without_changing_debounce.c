#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    settings.ioport.pullup_disable_in.mask = 2;
    digital_pins[Port_Input][1].mode.debounce = true;
    sys.ioinit_pending = true;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    CHECK(captured_input[0].pull_mode == PullMode_Up);
    CHECK(captured_input[1].pull_mode == PullMode_Down && captured_input[1].debounce);
    return EXIT_SUCCESS;
}
