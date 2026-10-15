#include "support/soft_limit_motion_host.h"
#include "kinematics/interface.h"
void corexy_init(void);
int main(void)
{
    prepare_soft_limit_motion();
    corexy_init();
    sync_position();
    queue_motion_program("G1X-20Y-10F100");
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    for(unsigned ticks = 0; ticks < 100; ticks++) {
        st_prep_buffer();
        stepper_driver_interrupt_handler();
    }
    unsigned before_a = axis_pulses[X_AXIS], before_b = axis_pulses[Y_AXIS];
    CHECK(before_a > 0 && before_b > 0);
    request_outside_soft_limits();
    CHECK(soft_hold_seen && soft_idle_seen);
    CHECK(axis_pulses[X_AXIS] >= before_a && axis_pulses[X_AXIS] < 2400);
    CHECK(axis_pulses[Y_AXIS] >= before_b && axis_pulses[Y_AXIS] < 800);
    CHECK(physical_position[X_AXIS] == -(int32_t)axis_pulses[X_AXIS]);
    CHECK(physical_position[Y_AXIS] == -(int32_t)axis_pulses[Y_AXIS]);
    CHECK(axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
