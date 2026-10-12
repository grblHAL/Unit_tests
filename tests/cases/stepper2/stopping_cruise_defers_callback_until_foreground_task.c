#include "support/secondary_stepper_host.h"

int main(void)
{
    st2_motor_t *motor = prepare_secondary_motor();
    st2_motor_register_stopped_callback(motor, motor_stopped);
    CHECK(st2_motor_move(motor, 0, 100, Stepper2_InfiniteSteps));
    cruise_motor(motor);
    unsigned before = motor_pulses;
    CHECK(st2_motor_stop(motor));
    finish_motor(motor);
    CHECK(motor_pulses > before);
    CHECK(stopped_calls == 0);
    engine_ticks += 3;
    engine_execute_tasks(STATE_IDLE);
    CHECK(stopped_calls == 1 && stopped_motor == motor);
    engine_ticks += 3;
    engine_execute_tasks(STATE_IDLE);
    CHECK(stopped_calls == 1);
    NEAR(st2_get_speed(motor), 0);
    return EXIT_SUCCESS;
}
