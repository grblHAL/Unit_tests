#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Output][0].mode.open_drain = true;
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "1") == Status_OK);
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "0") == Status_OK);
    CHECK(output_config_calls[0] == 2 && output_config_calls[1] == 0);
    CHECK(!captured_output[0].inverted && captured_output[0].open_drain);
    CHECK(settings.ioport.invert_out.mask == 0);
    return EXIT_SUCCESS;
}
