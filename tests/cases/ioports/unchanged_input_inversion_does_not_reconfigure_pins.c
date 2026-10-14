#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    CHECK(store_io_setting(Settings_IoPort_InvertIn, "3") == Status_OK);
    CHECK(store_io_setting(Settings_IoPort_InvertIn, "3") == Status_OK);
    CHECK(input_config_calls[0] == 1 && input_config_calls[1] == 1);
    CHECK(captured_input[0].inverted && captured_input[1].inverted);
    return EXIT_SUCCESS;
}
