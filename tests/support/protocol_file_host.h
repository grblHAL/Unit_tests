#pragma once
#include "support/file_stream_host.h"
#include "protocol.h"
#include "report.h"
#include "state_machine.h"
static unsigned protocol_file_end_calls, protocol_file_errors, protocol_sender_index, protocol_file_reads;
static status_code_t protocol_file_end_status, protocol_file_error_status;
static const char *protocol_sender_query = "$G\n";
static control_signals_t protocol_file_controls(void) { return (control_signals_t){0}; }
static bool protocol_file_connected(void) { return true; }
static void protocol_file_noop(void) { }
static void protocol_file_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static coolant_state_t protocol_file_coolant_state(void) { return (coolant_state_t){0}; }
static int32_t protocol_sender_read(void)
{
    CHECK(++protocol_file_reads < 10000);
    if(protocol_sender_query[protocol_sender_index]) return (uint8_t)protocol_sender_query[protocol_sender_index++];
    CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    return SERIAL_NO_DATA;
}
static status_code_t protocol_file_error(status_code_t status)
{
    protocol_file_errors++;
    protocol_file_error_status = status;
    return status; /* Provider retains the file until EOF so the final status can be observed. */
}
static status_code_t protocol_file_end(vfs_file_t *file, status_code_t status)
{
    CHECK(file == &fixture_file && hal.stream.file == file);
    protocol_file_end_calls++;
    protocol_file_end_status = status;
    stream_redirect_close(file);
    return status;
}
static void run_protocol_file(const char *program)
{
    prepare_file_stream(program);
    sys.cold_start = false;
    sys.driver_started = true;
    state_set(STATE_IDLE);
    stored_line_t empty = {0};
    for(unsigned i = 0; i < N_STARTUP_LINE; i++) settings_write_startup_line(i, empty);
    hal.control.get_state = protocol_file_controls;
    hal.stream.is_connected = protocol_file_connected;
    hal.stream.read = protocol_sender_read;
    hal.stream.reset_read_buffer = protocol_file_noop;
    hal.driver_reset = protocol_file_noop;
    hal.coolant.set_state = protocol_file_coolant;
    hal.coolant.get_state = protocol_file_coolant_state;
    report_init_fns();
    report_init();
    CHECK(stream_redirect_read("/fixture/program", protocol_file_error, protocol_file_end));
    CHECK(!protocol_main_loop());
    CHECK(protocol_file_end_calls == 1 && file_closes == 1);
    CHECK(hal.stream.file == NULL && hal.stream.read == protocol_sender_read);
    CHECK(protocol_sender_index == strlen(protocol_sender_query));
    CHECK(strstr(engine_output, "[GC:") != NULL);
}
