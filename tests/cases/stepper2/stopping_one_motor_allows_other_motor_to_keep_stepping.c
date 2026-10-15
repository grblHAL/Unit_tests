#include "support/secondary_stepper_pair_host.h"

int main(void)
{
    prepare_motor_pair();
    CHECK(st2_motor_stop(pair_x));
    for(unsigned i = 0; i < 1000 && st2_motor_running(pair_x); i++) tick_motor_pair();
    CHECK(!st2_motor_running(pair_x) && st2_motor_cruising(pair_y));
    int64_t stopped_position = st2_get_position(pair_x);
    int64_t running_position = st2_get_position(pair_y);
    for(unsigned i = 0; i < 20; i++) tick_motor_pair();
    CHECK(st2_get_position(pair_x) == stopped_position);
    CHECK(st2_get_position(pair_y) == running_position + 20);
    CHECK(st2_motor_stop(pair_y));
    finish_motor_pair();
    return EXIT_SUCCESS;
}
