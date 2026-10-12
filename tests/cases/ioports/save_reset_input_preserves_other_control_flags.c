#include "support/engine_host.h"
#include "ioports.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    settings.control_invert.feed_hold = true;
    xbar_t pin = { .function = Input_Reset };
    gpio_in_config_t config = { .inverted = true };
    ioport_save_input_settings(&pin, &config);
    CHECK(settings.control_invert.reset && settings.control_invert.feed_hold);
    config.inverted = false;
    ioport_save_input_settings(&pin, &config);
    CHECK(!settings.control_invert.reset && settings.control_invert.feed_hold);
    return EXIT_SUCCESS;
}
