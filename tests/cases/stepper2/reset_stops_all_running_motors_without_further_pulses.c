#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *first = prepare_secondary_motor();
    st2_motor_t *second = st2_motor_init(Y_AXIS, false);
    CHECK(second != NULL);
    CHECK(st2_motor_move(first, 0, 100, Stepper2_InfiniteSteps));
    CHECK(st2_motor_move(second, -1, 100, Stepper2_InfiniteSteps));
    tick_motor(first); tick_motor(second);
    CHECK(st2_motor_running(first) && st2_motor_running(second));
    unsigned before = motor_pulses;
    grbl.on_reset();
    CHECK(!st2_motor_running(first) && !st2_motor_running(second));
    tick_motor(first); tick_motor(second);
    CHECK(motor_pulses == before);
    CHECK(st2_set_position(first, 10) && st2_set_position(second, 20));
    CHECK(st2_get_position(first) == 10 && st2_get_position(second) == 20);
    return EXIT_SUCCESS;
}
