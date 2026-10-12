#include "support/spindle_override_host.h"
#include "check.h"
static float pwm_rpm;
static unsigned pwm_calls;
static uint_fast16_t pwm_value;
static uint_fast16_t encode_pwm(spindle_ptrs_t *spindle, float rpm) { CHECK(spindle == spindle_get(0)); pwm_rpm = rpm; return (uint_fast16_t)lroundf(rpm / 100); }
static void output_pwm(spindle_ptrs_t *spindle, uint_fast16_t value) { CHECK(spindle == spindle_get(0)); pwm_value = value; pwm_calls++; }
int main(void)
{
    spindle_ptrs_t *spindle = prepare_spindle_override();
    spindle->get_pwm = encode_pwm;
    spindle->update_pwm = output_pwm;
    RPM_NEAR(spindle_set_override(spindle, 150), 7500);
    RPM_NEAR(pwm_rpm, 7500);
    CHECK(pwm_value == 75);
    CHECK(pwm_calls == 1);
    CHECK(rpm_update_calls == 0);
    return EXIT_SUCCESS;
}
