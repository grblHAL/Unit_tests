#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    digital_pins[Port_Output][1].mode.output = true;
    xbar_t *pin = ioport_get_info(Port_Digital, Port_Output, 1);
    CHECK(pin != NULL);
    gpio_out_config_t config = { .open_drain = true };
    ioport_save_output_settings(pin, &config);
    CHECK(settings.ioport.od_enable_out.mask == 2);
    config.open_drain = false;
    ioport_save_output_settings(pin, &config);
    CHECK(settings.ioport.od_enable_out.mask == 0);
    return EXIT_SUCCESS;
}
