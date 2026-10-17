#pragma once
#include "support/fast_override_motion_host.h"
#include "support/hold_host.h"
static inline void execute_fast_short_segment_hold(void)
{
    queue_short_fast_segments();
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned tick = 0; tick < 200000 && physical_position[X_AXIS] < 11760; tick++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    CHECK(physical_position[X_AXIS] == 11760);
    CHECK(st_get_realtime_rate() > 10000);
    hold_motion();
    CHECK(physical_position[X_AXIS] > 11760 && physical_position[X_AXIS] < 24000);
    int32_t stopped = physical_position[X_AXIS];
    for(unsigned i = 0; i < 32; i++) CHECK(protocol_exec_rt_system());
    CHECK(physical_position[X_AXIS] == stopped);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    finish_motion_pulses();
    CHECK(physical_position[X_AXIS] == 24000 && sys.position[X_AXIS] == 24000);
    CHECK(axis_pulses[X_AXIS] == 24000 && wake_calls == 2);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL);
}
