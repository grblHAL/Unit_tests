#include "support/soft_limit_motion_host.h"
int main(void)
{
    prepare_soft_limit_motion();
    queue_motion_program("G1X-20F100");
    queue_motion_program("G1X-40F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    unsigned before = axis_pulses[X_AXIS];
    CHECK(before > 0 && before < 1600);
    request_outside_soft_limits();
    CHECK(soft_hold_seen && soft_idle_seen);
    CHECK(axis_pulses[X_AXIS] >= before && axis_pulses[X_AXIS] < 1600);
    CHECK(physical_position[X_AXIS] == -(int32_t)axis_pulses[X_AXIS]);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
