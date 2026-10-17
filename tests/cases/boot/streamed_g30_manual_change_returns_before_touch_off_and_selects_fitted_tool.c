#include "support/boot_tool_position_reset_host.h"
int main(void)
{
    prepare_boot_streamed_manual_change(true);
    boot_tool_plain_manual = false;
    boot_program = "$H\nG0X-2Y-3Z-1\nT3M6\n" "\xA3\x81" "G10L2P1Z0\n" "\x81" "$G\n";
    CHECK(grbl_enter() == 0);
    CHECK(boot_tool_exit_sent && !boot_tool_reset_sent);
    CHECK(!gc_state.tool_change && gc_state.tool->tool_id == 3);
    CHECK(sys.position[X_AXIS] == -160 && sys.position[Y_AXIS] == -240 && sys.position[Z_AXIS] == -80);
    CHECK(boot_tool_rt_handler == protocol_enqueue_realtime_command);
    CHECK(stream_is_rx_suspended() == StreamSuspend_Off);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(sys.position[axis] == boot_motor_position[axis] - boot_tool_home_offset[axis]);
    CHECK(strstr(engine_output, " T3 ") != NULL);
    CHECK(strstr(engine_output, "error:") == NULL);
    return EXIT_SUCCESS;
}
