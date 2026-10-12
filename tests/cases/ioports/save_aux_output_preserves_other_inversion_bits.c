#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    digital_pins[Port_Output][1].mode.output = true;
    settings.ioport.invert_out.mask = 1;
    xbar_t *pin = ioport_get_info(Port_Digital, Port_Output, 1);
    CHECK(pin != NULL);
    gpio_out_config_t config = { .inverted = true };
    ioport_save_output_settings(pin, &config);
    CHECK(settings.ioport.invert_out.mask == 3);
    config.inverted = false;
    ioport_save_output_settings(pin, &config);
    CHECK(settings.ioport.invert_out.mask == 1);
    return EXIT_SUCCESS;
}
