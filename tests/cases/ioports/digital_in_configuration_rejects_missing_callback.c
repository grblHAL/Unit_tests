#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Input][0].config = NULL;
    gpio_in_config_t config = {0};
    CHECK(!ioport_digital_in_config(0, &config));
    CHECK(input_config_calls[0] == 0);
    return EXIT_SUCCESS;
}
