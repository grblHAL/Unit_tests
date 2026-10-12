#include "support/ioports_analog_host.h"
#include "check.h"

int main(void)
{
    prepare_analog_ports();
    pwm_config_t config = {.freq_hz = 50, .min = 0, .max = 180, .min_value = 5, .max_value = 10, .invert = true, .servo_mode = true};
    CHECK(ioport_analog_out_config(1, &config));
    CHECK(pwm_config_calls == 1);
    CHECK(configured_pwm_pin == &analog_pins[Port_Output][1]);
    NEAR(captured_pwm.freq_hz, 50);
    NEAR(captured_pwm.max, 180);
    NEAR(captured_pwm.min_value, 5);
    NEAR(captured_pwm.max_value, 10);
    CHECK(captured_pwm.invert && captured_pwm.servo_mode);
    return EXIT_SUCCESS;
}
