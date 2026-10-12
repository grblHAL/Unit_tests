#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    gpio_in_config_t config = {0};
    CHECK(!ioport_digital_in_config(2, &config));
    CHECK(input_config_calls[0] == 0 && input_config_calls[1] == 0);
    return EXIT_SUCCESS;
}
