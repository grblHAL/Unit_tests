#include "support/toolsetter_hook_host.h"

static bool reset_at_position(tool_data_t *tool, coord_data_t *position, bool at_fixture, bool on)
{
    bool selected = select_fixture_probe(tool, position, at_fixture, on);
    if(position)
        CHECK(protocol_enqueue_realtime_command(CMD_RESET));
    return selected;
}

int main(void)
{
    prepare_fixture_probe_hook(ToolChange_Manual_G59_3);
    install_manual_change_interface();
    grbl.on_probe_toolsetter = reset_at_position;
    tool_data_t next = {.tool_id = 3};
    hal.tool.select(&next, true);
    CHECK(hal.tool.change(&gc_state) == Status_Reset);
    CHECK(setter_position_calls == 1 && reset_calls == 1);
    CHECK(sys.abort && !HOST_PARSER_FLAGS.tool_change);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(physical_position[X_AXIS] == 160 && physical_position[Y_AXIS] == 240);
    CHECK(physical_position[Z_AXIS] == -80 && axis_pulses[Z_AXIS] == 0);
    CHECK(manual_tool_changed_calls == 0);
    return EXIT_SUCCESS;
}
