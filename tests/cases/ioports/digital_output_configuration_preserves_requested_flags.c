#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    gpio_out_config_t config = {.inverted = true, .open_drain = true};
    CHECK(ioport_digital_out_config(1, &config));
    CHECK(output_config_calls[0] == 0 && output_config_calls[1] == 1);
    CHECK(captured_output[1].inverted && captured_output[1].open_drain);
    return EXIT_SUCCESS;
}
