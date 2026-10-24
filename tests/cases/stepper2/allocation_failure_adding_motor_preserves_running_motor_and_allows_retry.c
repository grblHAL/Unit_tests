#include "support/secondary_stepper_host.h"
#include "support/calloc_failure_host.h"
int main(void)
{
    st2_motor_t *first = prepare_secondary_motor();
    CHECK(st2_motor_move(first, 20, 100, Stepper2_Steps));
    tick_motor(first);
    CHECK(motor_pulses == 1 && st2_get_position(first) == 1);
    settings_changed_ptr settings_handler = grbl.on_settings_changed;
    fail_calloc = true;
    st2_motor_t *second = st2_motor_init(Y_AXIS, false);
    fail_calloc = false;
    CHECK(second == NULL && failed_calloc_calls == 1);
    CHECK(grbl.on_settings_changed == settings_handler);
    CHECK(st2_motor_running(first) && motor_pulses == 1);
    finish_motor(first);
    CHECK(st2_get_position(first) == 20 && motor_pulses == 20);
    second = st2_motor_init(Y_AXIS, false);
    CHECK(second != NULL);
    CHECK(st2_motor_move(second, -5, 50, Stepper2_Steps));
    finish_motor(second);
    CHECK(st2_get_position(second) == -5 && motor_pulses == 25);
    CHECK(st2_get_position(first) == 20 && !st2_motor_running(first));
    CHECK(grbl.on_settings_changed == settings_handler);
    return EXIT_SUCCESS;
}
