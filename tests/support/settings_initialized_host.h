#pragma once
#include "support/settings_host.h"
static inline bool host_save_tool(tool_data_t *tool)
{
#ifdef HOST_TOOL_PERSIST_API
    return grbl.tool_table.set_tool(tool, true);
#else
    return grbl.tool_table.set_tool(tool);
#endif
}
static inline void prepare_initialized_settings(float minimum_pulse_us)
{
    prepare_settings_store();
    report_init_fns();
    hal.step_us_min = minimum_pulse_us;
    settings.version.id = SETTINGS_VERSION;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    settings_write_global();
    settings_init();
    change_callbacks = 0;
}
