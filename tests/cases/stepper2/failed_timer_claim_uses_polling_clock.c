#include "support/secondary_timer_host.h"

int main(void)
{
    timer_claim_fails = true;
    st2_motor_t *motor = prepare_timer_motor();
    CHECK(timer_claims > 0 && st2_motor_poll(motor));
    CHECK(st2_motor_move(motor, 0, 100, Stepper2_InfiniteSteps));
    tick_motor(motor);
    CHECK(motor_pulses == 1 && timer_starts == 0);
    return EXIT_SUCCESS;
}
