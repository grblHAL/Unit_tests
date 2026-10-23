#include "support/motion_program_host.h"
#include "protocol.h"
int main(void)
{
    prepare_motion_program();
    CHECK(hal.reboot == NULL);
    queue_motion_program("G1X1F100");
    plan_block_t *cut = plan_get_current_block();
    CHECK(protocol_enqueue_realtime_command(ASCII_ESC));
    protocol_enqueue_realtime_command(CMD_REBOOT);
    CHECK(plan_get_current_block() == cut && !sys.abort);
    CHECK(state_get() == STATE_IDLE && sys.rt_exec_state == 0);
    CHECK(physical_position[X_AXIS] == 0 && axis_pulses[X_AXIS] == 0);
    CHECK(protocol_enqueue_realtime_command(CMD_CYCLE_START));
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_CYCLE);
    execute_motion_program();
    CHECK(protocol_exec_rt_system());
    CHECK(state_get() == STATE_IDLE && !sys.abort);
    CHECK(physical_position[X_AXIS] == 80 && sys.position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
