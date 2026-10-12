#pragma once
#include "support/settings_host.h"
#include "report.h"
#include "state_machine.h"
static bool file_connected(void) { return true; }
static unsigned file_callback_calls;
static bool file_callback_start[4];
static void file_callback(bool start)
{
    CHECK(file_callback_calls < 4);
    file_callback_start[file_callback_calls++] = start;
}
static inline void prepare_settings_file(void)
{
    prepare_settings_store();
    hal.step_us_min = 2;
    grbl.on_file_demarcate = file_callback;
    settings.version.id = SETTINGS_VERSION;
    hal.nvs.put_byte(0, SETTINGS_VERSION);
    settings_write_global();
    settings_init();
    hal.stream.is_connected = file_connected;
    report_init_fns();
    report_init();
    change_callbacks = 0;
}
