#include "support/ioports_analog_host.h"
#include "check.h"

int main(void)
{
    prepare_analog_ports();
    analog_pins[Port_Output][0].config = NULL;
    pwm_config_t config = {.freq_hz = 50};
    CHECK(!ioport_analog_out_config(0, &config));
    CHECK(pwm_config_calls == 0);
    return EXIT_SUCCESS;
}
