#include "support/boot_tool_position_reset_host.h"
int main(void)
{
    prepare_boot_streamed_manual_change(false);
    CHECK(grbl_enter() == 0);
    CHECK(boot_tool_exit_sent && !boot_tool_reset_sent);
    CHECK(!HOST_PARSER_FLAGS.tool_change && gc_state.tool->tool_id == 3);
    CHECK(sys.position[X_AXIS] == -160 && sys.position[Y_AXIS] == -240);
    CHECK(sys.position[Z_AXIS] == -10);
    CHECK(boot_tool_rt_handler == protocol_enqueue_realtime_command);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(sys.position[axis] == boot_motor_position[axis] - boot_tool_home_offset[axis]);
    return EXIT_SUCCESS;
}
