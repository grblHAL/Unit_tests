#pragma once
#include "support/motion_program_host.h"
static inline void start_hold_move(void)
{
    prepare_motion_program();
    queue_motion_program("G1X20F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE);
    CHECK(wake_calls == 1);
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
}
static inline void finish_motion_pulses(void)
{
    for(unsigned ticks = 0; ticks < 200000 && !(sys.rt_exec_state & EXEC_CYCLE_COMPLETE); ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(sys.rt_exec_state & EXEC_CYCLE_COMPLETE);
}
static inline void hold_motion(void)
{
    CHECK(protocol_enqueue_realtime_command(CMD_FEED_HOLD));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_HOLD);
    CHECK(sys.holding_state == Hold_Pending);
    finish_motion_pulses();
    CHECK(protocol_exec_rt_system());
    CHECK(sys.holding_state == Hold_Complete);
    CHECK(state_get() == STATE_HOLD);
    CHECK(sys.suspend);
    CHECK(plan_get_current_block() != NULL);
}
