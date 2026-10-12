#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    CHECK(store_io_setting(Settings_IoPort_InvertIn, "2") == Status_OK);
    CHECK(input_config_calls[0] == 0 && input_config_calls[1] == 1);
    CHECK(captured_input[1].inverted && captured_input[1].pull_mode == PullMode_Up);
    CHECK(settings.ioport.invert_in.mask == 2);
    return EXIT_SUCCESS;
}
