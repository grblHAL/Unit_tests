#pragma once
#include "support/secondary_stepper_host.h"

static st2_motor_t *pair_x, *pair_y;
static inline void tick_motor_pair(void)
{
    motor_clock += 1000000;
    st2_motor_run(pair_x);
    st2_motor_run(pair_y);
}
static inline void prepare_motor_pair(void)
{
    pair_x = prepare_secondary_motor();
    pair_y = st2_motor_init(Y_AXIS, false);
    CHECK(pair_y != NULL);
    CHECK(st2_motor_move(pair_x, 0, 100, Stepper2_InfiniteSteps));
    CHECK(st2_motor_move(pair_y, 0, 200, Stepper2_InfiniteSteps));
    for(unsigned i = 0; i < 1000 && !(st2_motor_cruising(pair_x) && st2_motor_cruising(pair_y)); i++) tick_motor_pair();
    CHECK(st2_motor_cruising(pair_x) && st2_motor_cruising(pair_y));
}
static inline void finish_motor_pair(void)
{
    for(unsigned i = 0; i < 1000 && (st2_motor_running(pair_x) || st2_motor_running(pair_y)); i++) tick_motor_pair();
    CHECK(!st2_motor_running(pair_x) && !st2_motor_running(pair_y));
    CHECK((uint64_t)(st2_get_position(pair_x) + st2_get_position(pair_y)) == motor_pulses);
}
