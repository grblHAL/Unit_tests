#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "2") == Status_OK);
    CHECK(input_config_calls[1] == 1);
    pull_mode_t live_pull_mode = captured_input[1].pull_mode;
    sys.ioinit_pending = true;
    grbl.on_settings_changed(&settings, (settings_changed_flags_t){0});
    CHECK(input_config_calls[1] == 2);
    CHECK(live_pull_mode == captured_input[1].pull_mode);
    return EXIT_SUCCESS;
}
