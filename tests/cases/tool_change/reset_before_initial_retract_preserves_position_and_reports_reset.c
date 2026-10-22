#include "support/tool_change_host.h"

static unsigned reset_polls;
static void reset_before_retract(sys_state_t state)
{
    CHECK(state == STATE_IDLE);
    CHECK(++reset_polls == 1);
    CHECK(protocol_enqueue_realtime_command(CMD_RESET));
}

int main(void)
{
    prepare_tool_change_motion();
    install_manual_change_interface();
    tool_data_t next = {.tool_id = 3};
    hal.tool.select(&next, true);
    grbl.on_execute_realtime = reset_before_retract;
    CHECK(hal.tool.change(&gc_state) == Status_Reset);
    CHECK(reset_polls == 1 && reset_calls == 1);
    CHECK(sys.abort && !HOST_PARSER_FLAGS.tool_change);
    CHECK(plan_get_current_block() == NULL);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(physical_position[Z_AXIS] == -80);
    CHECK(manual_tool_changed_calls == 0);
    return EXIT_SUCCESS;
}
