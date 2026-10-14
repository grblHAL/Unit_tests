#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "1") == Status_OK);
    CHECK(captured_input[0].pull_mode == PullMode_Down);
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "0") == Status_OK);
    CHECK(input_config_calls[0] == 2 && input_config_calls[1] == 0);
    CHECK(captured_input[0].pull_mode == PullMode_Up);
    CHECK(settings.ioport.pullup_disable_in.mask == 0);
    return EXIT_SUCCESS;
}
