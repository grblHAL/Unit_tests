#pragma once
#include "support/file_stream_host.h"
#include "support/settings_initialized_host.h"
#include "protocol.h"
static inline vfs_file_t *prepare_ngc_tool_file(void)
{
    prepare_file_stream("");
    hal.step_us_min = 2;
    grbl.on_settings_changed = changed_settings;
    settings.version.id = SETTINGS_VERSION;
    hal.nvs.put_byte(0, SETTINGS_VERSION); settings_write_global(); settings_init();
    gc_init(false); grbl.on_execute_realtime = protocol_execute_noop;
    CHECK(grbl.tool_table.n_tools == 4);
    tool_data_t tool = {.tool_id = 2, .offset.values = {1, 2, 3}};
    CHECK(grbl.tool_table.set_tool(&tool));
    vfs_file_t *file = stream_redirect_read("/fixture/program", NULL, NULL);
    CHECK(file != NULL && hal.stream.file == file); return file;
}
