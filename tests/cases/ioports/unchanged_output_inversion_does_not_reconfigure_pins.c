#include "support/ioports_settings_host.h"

int main(void)
{
    prepare_io_settings();
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "3") == Status_OK);
    CHECK(store_io_setting(Settings_IoPort_InvertOut, "3") == Status_OK);
    CHECK(output_config_calls[0] == 1 && output_config_calls[1] == 1);
    CHECK(captured_output[0].inverted && captured_output[1].inverted);
    return EXIT_SUCCESS;
}
