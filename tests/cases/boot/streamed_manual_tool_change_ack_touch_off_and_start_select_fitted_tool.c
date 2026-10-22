#include "support/boot_tool_position_reset_host.h"
int main(void)
{
    prepare_boot_streamed_manual_change(true);
    CHECK(grbl_enter() == 0);
    CHECK(boot_tool_positioning && boot_tool_exit_sent && !boot_tool_reset_sent);
    CHECK(!HOST_PARSER_FLAGS.tool_change && gc_state.tool->tool_id == 3);
    CHECK(boot_tool_rt_handler == protocol_enqueue_realtime_command);
    CHECK(sys.position[X_AXIS] == -160 && sys.position[Y_AXIS] == -240 && sys.position[Z_AXIS] == -80);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(sys.position[axis] == boot_motor_position[axis] - boot_tool_home_offset[axis]);
    CHECK(strstr(engine_output, " T3 ") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
