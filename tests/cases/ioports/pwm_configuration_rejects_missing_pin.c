#include "support/ioports_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_port();
    pwm_config_t config = {.freq_hz = 1000};
    CHECK(!ioport_digital_pwm_config(2, &config));
    CHECK(pwm_config_calls == 0);
    return EXIT_SUCCESS;
}
