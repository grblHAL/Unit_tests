#include "support/ioports_settings_host.h"
#include "check.h"

int main(void)
{
    prepare_io_settings();
    digital_pins[Port_Output][0].mode.pwm = true;
    gpio_out_config_t config = {.inverted = true};
    CHECK(!ioport_digital_out_config(0, &config));
    CHECK(output_config_calls[0] == 0);
    return EXIT_SUCCESS;
}
