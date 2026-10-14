#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "3") == Status_OK);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "3") == Status_OK);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    return EXIT_SUCCESS;
}
