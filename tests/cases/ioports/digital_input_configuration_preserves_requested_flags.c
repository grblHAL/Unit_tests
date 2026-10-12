#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    gpio_in_config_t config = {.inverted = true, .debounce = true, .pull_mode = PullMode_Down};
    CHECK(ioport_digital_in_config(1, &config));
    CHECK(input_config_calls[0] == 0 && input_config_calls[1] == 1);
    CHECK(captured_input[1].inverted && captured_input[1].debounce);
    CHECK(captured_input[1].pull_mode == PullMode_Down);
    return EXIT_SUCCESS;
}
