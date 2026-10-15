#include "support/secondary_stepper_pair_host.h"

int main(void)
{
    prepare_motor_pair();
    st2_motor_set_speed(pair_x, 50);
    for(unsigned i = 0; i < 1000 && !st2_motor_cruising(pair_x); i++) {
        tick_motor_pair();
        CHECK(st2_motor_cruising(pair_y));
        CHECK(fabsf(st2_get_speed(pair_y) - 200) < .2f);
    }
    CHECK(st2_motor_cruising(pair_x));
    CHECK(fabsf(st2_get_speed(pair_x) - 50) < .2f);
    CHECK(st2_motor_stop(pair_x) && st2_motor_stop(pair_y));
    finish_motor_pair();
    return EXIT_SUCCESS;
}
