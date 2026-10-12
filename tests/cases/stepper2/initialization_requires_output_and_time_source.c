#include "support/secondary_stepper_host.h"

int main(void)
{
    engine_prepare();
    CHECK(st2_motor_init(X_AXIS, false) == NULL);
    hal.stepper.output_step = capture_motor_step;
    CHECK(st2_motor_init(X_AXIS, false) == NULL);
    hal.get_micros = motor_micros;
    st2_motor_t *motor = st2_motor_init(X_AXIS, false);
    CHECK(motor != NULL && st2_motor_poll(motor));
    CHECK(motor_pulses == 0);
    return EXIT_SUCCESS;
}
