#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    settings.probe.invert_probe_pin = true;
    xbar_t pin = { .function = Input_Probe };
    gpio_in_config_t config = { .inverted = false };
    ioport_save_input_settings(&pin, &config);
    CHECK(!settings.probe.invert_probe_pin);
    return EXIT_SUCCESS;
}
