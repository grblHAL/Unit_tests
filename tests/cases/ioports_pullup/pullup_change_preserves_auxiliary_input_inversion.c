#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][0].mode.inverted = true;
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "1") == Status_OK);
    CHECK(captured_input[0].inverted);
    CHECK(captured_input[0].pull_mode == PullMode_Down);
    return EXIT_SUCCESS;
}
