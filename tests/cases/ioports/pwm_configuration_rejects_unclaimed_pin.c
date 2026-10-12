#include "support/ioports_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_ioports();
    digital_pins[Port_Output][0].config = configure_pwm;
    digital_pins[Port_Output][0].cap.pwm = true;
    pwm_config_t config = {.freq_hz = 1000};
    CHECK(!ioport_digital_pwm_config(0, &config));
    CHECK(pwm_config_calls == 0);
    return EXIT_SUCCESS;
}
