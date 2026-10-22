#pragma once
#include "support/tool_change_host.h"

static float reset_after_x;
static unsigned queue_reset_polls, queue_reset_commands;
static void reset_after_queued_target(sys_state_t state)
{
    CHECK(state == STATE_IDLE && ++queue_reset_polls < 10);
    plan_block_t *last = plan_get_recent_block();
    if(last && last->target_mm[X_AXIS] == reset_after_x) {
        CHECK(++queue_reset_commands == 1);
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    }
}
static inline void check_g30_queue_reset(float previous_x)
{
    prepare_tool_change_motion();
    install_manual_change_interface();
    coord_system_data_t g30 = {.coord = {.x = 4, .y = 5, .z = -0.5f}};
    settings_write_coord_data(CoordinateSystem_G30, &g30);
    settings.flags.tool_change_at_g30 = true;
    sys.homed.mask = X_AXIS_BIT | Y_AXIS_BIT | Z_AXIS_BIT;
    tool_data_t next = {.tool_id = 3};
    hal.tool.select(&next, true);
    reset_after_x = previous_x;
    grbl.on_execute_realtime = reset_after_queued_target;
    CHECK(hal.tool.change(&gc_state) == Status_Reset);
    CHECK(queue_reset_commands == 1 && reset_calls == 1);
    CHECK(sys.abort && !HOST_PARSER_FLAGS.tool_change);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(physical_position[Z_AXIS] == -80 && manual_tool_changed_calls == 0);
    plan_block_t *last = plan_get_recent_block();
    CHECK(last != NULL);
    NEAR(last->target_mm[X_AXIS], previous_x);
    NEAR(last->target_mm[Z_AXIS], 0);
}
