#include "support/hold_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); for(unsigned i=0;i<N_AXIS;i++) settings.axis[i].jerk=60000;
    queue_motion_program("G1X20F100"); CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START)); CHECK(protocol_exec_rt_system());
    for(unsigned ticks=0;ticks<100;ticks++) { st_prep_buffer(); stepper_driver_interrupt_handler(); }
    hold_motion(); CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START)); CHECK(protocol_exec_rt_system()); CHECK(state_get()==STATE_CYCLE);
    finish_motion_pulses(); CHECK(axis_pulses[X_AXIS]==1600); CHECK(physical_position[X_AXIS]==1600); CHECK(sys.position[X_AXIS]==1600);
    CHECK(plan_get_current_block()==NULL); CHECK(protocol_exec_rt_system()); CHECK(state_get()==STATE_IDLE);
    return EXIT_SUCCESS;
}
