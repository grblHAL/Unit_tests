#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Output][1].mode.open_drain = true;
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "2") == Status_OK);
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 1);
    CHECK(captured_output[1].inverted && captured_output[1].open_drain);
    CHECK(settings.ioport.invert_out.mask == 2);
    return EXIT_SUCCESS;
}
