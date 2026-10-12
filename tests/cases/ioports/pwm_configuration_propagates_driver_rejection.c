#include "support/ioports_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_port();
    pwm_config_result = false;
    pwm_config_t config = {.freq_hz = 1000};
    CHECK(!ioport_digital_pwm_config(claimed_pwm_port, &config));
    CHECK(pwm_config_calls == 1);
    return EXIT_SUCCESS;
}
