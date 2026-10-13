#pragma once
#include "support/program_end_host.h"
#include "support/file_stream_host.h"
static unsigned file_marker_calls;
static bool last_file_marker;
static void file_demarcated(bool start) { file_marker_calls++; last_file_marker = start; }
static inline void prepare_marker_file(bool check_mode)
{
    prepare_file_stream("%\nG21\n%\n");
    grbl.on_execute_realtime = protocol_execute_noop;
    grbl.on_program_completed = program_completed;
    grbl.on_file_demarcate = file_demarcated;
    hal.control.get_state = coolant_controls;
    hal.stream.is_connected = coolant_connected;
    hal.coolant.get_state = get_coolant;
    report_init_fns();
    report_init();
    state_set(check_mode ? STATE_CHECK_MODE : STATE_IDLE);
    CHECK(stream_redirect_read("/fixture/program", NULL, NULL));
}
