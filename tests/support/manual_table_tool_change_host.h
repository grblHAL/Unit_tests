#pragma once
#include "support/tool_change_host.h"
#include "support/settings_initialized_host.h"

static inline void prepare_manual_table_change(void)
{
    prepare_tool_change();
    hal.step_us_min = 2;
    settings.version.id = SETTINGS_VERSION;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    settings_write_global();
    settings_init();
    CHECK(grbl.tool_table.n_tools == 4);
    gc_init(false);
    tc_init();
    install_manual_change_interface();
    tool_data_t selected = {.tool_id = 3, .offset.values = {0, 0, 2}};
    tool_data_t alternate = {.tool_id = 4, .offset.values = {0, 0, 3}};
    CHECK(host_save_tool(&selected));
    CHECK(host_save_tool(&alternate));
}
static inline void acknowledge_table_change(void)
{
    resume_manual_change();
    CHECK(protocol_execute_realtime());
    CHECK(!gc_state.tool_change && gc_state.tool->tool_id == 3);
}
static inline void cut_with_table_offset(int32_t expected_z)
{
    queue_motion_program("G1Z-5F100");
    execute_motion_program();
    CHECK(physical_position[Z_AXIS] == expected_z && sys.position[Z_AXIS] == expected_z);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == (unsigned)-expected_z);
}
