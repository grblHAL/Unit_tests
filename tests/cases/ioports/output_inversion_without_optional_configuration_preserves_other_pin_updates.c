#include "support/ioports_settings_host.h"
#include "check.h"
int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Output][0].config = NULL;
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "3") == Status_OK);
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 1);
    CHECK(captured_output[1].inverted);
    CHECK(settings.ioport.invert_out.mask == 3);
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "0") == Status_OK);
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 2);
    CHECK(!captured_output[1].inverted);
    CHECK(settings.ioport.invert_out.mask == 0);
    CHECK(input_config_calls[0] == 0 && input_config_calls[1] == 0);
    return EXIT_SUCCESS;
}
