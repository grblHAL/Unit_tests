#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    settings.ioport.invert_in.mask = 1;
    xbar_t *pin = ioport_get_info(Port_Digital, Port_Input, 1);
    CHECK(pin != NULL);
    gpio_in_config_t config = { .inverted = true, .pull_mode = PullMode_Up };
    ioport_save_input_settings(pin, &config);
    CHECK(settings.ioport.invert_in.mask == 3);
    config.inverted = false;
    ioport_save_input_settings(pin, &config);
    CHECK(settings.ioport.invert_in.mask == 1);
    return EXIT_SUCCESS;
}
