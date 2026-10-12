#include "support/ioports_pwm_host.h"
#include "check.h"

int main(void)
{
    prepare_pwm_port();
    pwm_config_t config = {.freq_hz = 1234, .min = 2, .max = 98, .off_value = 3, .min_value = 4, .max_value = 95, .invert = true, .servo_mode = true};
    CHECK(ioport_digital_pwm_config(claimed_pwm_port, &config));
    CHECK(pwm_config_calls == 1);
    CHECK(configured_pwm_pin == &digital_pins[Port_Output][0]);
    NEAR(captured_pwm.freq_hz, 1234);
    NEAR(captured_pwm.min, 2);
    NEAR(captured_pwm.max, 98);
    NEAR(captured_pwm.off_value, 3);
    NEAR(captured_pwm.min_value, 4);
    NEAR(captured_pwm.max_value, 95);
    CHECK(captured_pwm.invert && captured_pwm.servo_mode);
    return EXIT_SUCCESS;
}
