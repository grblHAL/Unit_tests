#include "support/ioports_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    xbar_t *pin = ioport_get_info(Port_Digital, Port_Input, 1);
    CHECK(pin != NULL);
    gpio_in_config_t config = { .pull_mode = PullMode_None };
    ioport_save_input_settings(pin, &config);
    CHECK(settings.ioport.pullup_disable_in.mask == 2);
    config.pull_mode = PullMode_Up;
    ioport_save_input_settings(pin, &config);
    CHECK(settings.ioport.pullup_disable_in.mask == 0);
    return EXIT_SUCCESS;
}
