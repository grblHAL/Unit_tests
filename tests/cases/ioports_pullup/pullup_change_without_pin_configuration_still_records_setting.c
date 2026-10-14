#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][1].config = NULL;
    CHECK(store_io_setting(Settings_IoPort_Pullup_Disable, "2") == Status_OK);
    CHECK(input_config_calls[0] == 0 && input_config_calls[1] == 0);
    CHECK(settings.ioport.pullup_disable_in.mask == 2);
    return EXIT_SUCCESS;
}
