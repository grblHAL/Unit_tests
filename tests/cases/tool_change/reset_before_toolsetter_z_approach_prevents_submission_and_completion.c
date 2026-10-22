#include "support/toolsetter_hook_host.h"

static unsigned approach_polls, approach_resets;
static void reset_before_setter_z(sys_state_t state)
{
    CHECK(state == STATE_IDLE && ++approach_polls < 10);
    plan_block_t *last = plan_get_recent_block();
    if(last && last->target_mm[X_AXIS] == 1 && last->target_mm[Y_AXIS] == 1) {
        CHECK(++approach_resets == 1);
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
}

int main(void)
{
    prepare_fixture_probe_hook(ToolChange_Manual_G59_3);
    install_manual_change_interface();
    tool_data_t next = {.tool_id = 3};
    hal.tool.select(&next, true);
    grbl.on_execute_realtime = reset_before_setter_z;
    CHECK(hal.tool.change(&gc_state) == Status_Reset);
    CHECK(approach_resets == 1 && reset_calls == 1 && setter_position_calls == 1);
    CHECK(sys.abort && !HOST_PARSER_FLAGS.tool_change);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(physical_position[Z_AXIS] == -80 && manual_tool_changed_calls == 0);
    plan_block_t *last = plan_get_recent_block();
    CHECK(last != NULL);
    NEAR(last->target_mm[Z_AXIS], 0);
    return EXIT_SUCCESS;
}
