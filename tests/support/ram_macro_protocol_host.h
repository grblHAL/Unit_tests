#pragma once
#include "support/nested_ram_stream_host.h"
#include "ngc_params.h"
static vfs_file_t *ram_macro_files[3];
static unsigned ram_macro_eofs[3], ram_macro_errors[3], ram_macro_calls;
static unsigned ram_sender_index, ram_sender_reads;
static float ram_arguments[2], ram_return_arguments[3], ram_return_named[3];
static bool ram_capture_named;
static uint_fast8_t ram_return_scopes[3];
static line_number_t ram_return_lines[3];
static status_code_t ram_return_status[3];
static const char *ram_sender_query = "$G\n";
static unsigned ram_owner(vfs_file_t *file)
{
    for(unsigned i = 0; i < 3; i++) if(file == ram_macro_files[i]) return i;
    CHECK(false);
    return 0;
}
static control_signals_t ram_protocol_controls(void) { return (control_signals_t){0}; }
static coolant_state_t ram_protocol_coolant(void) { return (coolant_state_t){0}; }
static void ram_protocol_set_coolant(coolant_state_t state) { CHECK(state.mask == 0); }
static int32_t ram_sender_read(void)
{
    CHECK(++ram_sender_reads < 10000);
    if(ram_sender_query[ram_sender_index]) return (uint8_t)ram_sender_query[ram_sender_index++];
    CHECK(protocol_enqueue_realtime_command(CMD_EXIT));
    return SERIAL_NO_DATA;
}
static status_code_t ram_protocol_error(status_code_t status)
{
    CHECK(status != Status_OK);
    ram_macro_errors[ram_owner(hal.stream.file)]++;
    return status;
}
static status_code_t ram_protocol_eof(vfs_file_t *file, status_code_t status)
{
    unsigned owner = ram_owner(file);
    ram_macro_eofs[owner]++;
    ram_return_status[owner] = status;
    ram_return_scopes[owner] = ngc_call_level();
    ram_return_lines[owner] = grbl.on_line_number_assigned(0);
    CHECK(ngc_param_get(1, &ram_return_arguments[owner]));
    if(ram_capture_named) CHECK(ngc_named_param_get("note", &ram_return_named[owner]));
    stream_redirect_close(file);
    if(owner) {
        CHECK(ngc_call_level() == owner);
        ngc_call_pop(); /* Status_Handled transfers asynchronous scope ownership to the loader. */
        CHECK(ngc_call_level() == owner - 1);
    }
    return status;
}
static status_code_t ram_execute_macro(macro_id_t id, line_number_t line, parameter_words_t words, uint32_t repeats)
{
    (void)line;
    CHECK((id == 10 || id == 20) && words.a && repeats == 1);
    unsigned owner = id == 10 ? 1 : 2;
    CHECK(ngc_call_level() == owner);
    CHECK(ngc_param_get(1, &ram_arguments[owner - 1]));
    ram_macro_calls++;
    ram_macro_files[owner] = stream_redirect_read(owner == 1 ? "/ram/sub" : "/ram/leaf", ram_protocol_error, ram_protocol_eof);
    CHECK(ram_macro_files[owner] != NULL);
    return Status_Handled;
}
static inline void run_ram_macro_protocol(const char *main_program, const char *sub_program, const char *leaf_program)
{
    prepare_ram_stream_environment();
    sys.cold_start = false;
    sys.driver_started = true;
    stored_line_t empty = {0};
    for(unsigned i = 0; i < N_STARTUP_LINE; i++) settings_write_startup_line(i, empty);
    hal.control.get_state = ram_protocol_controls;
    hal.coolant.get_state = ram_protocol_coolant;
    hal.coolant.set_state = ram_protocol_set_coolant;
    hal.stream.read = ram_sender_read;
    hal.stream.reset_read_buffer = nested_driver_reset;
    grbl.on_execute_realtime = protocol_execute_noop;
    grbl.on_file_end = NULL;
    grbl.on_macro_execute = ram_execute_macro;
    nested_create_file("/ram/main", main_program);
    nested_create_file("/ram/sub", sub_program);
    nested_create_file("/ram/leaf", leaf_program);
    ram_macro_files[0] = stream_redirect_read("/ram/main", ram_protocol_error, ram_protocol_eof);
    CHECK(ram_macro_files[0] != NULL);
    CHECK(!protocol_main_loop());
    CHECK(ram_macro_calls == 2 && ngc_call_level() == 0);
    for(unsigned i = 0; i < 3; i++) {
        CHECK(ram_macro_eofs[i] == 1);
        CHECK(ram_return_scopes[i] == i);
    }
    CHECK(!stream_is_file() && hal.stream.read == ram_sender_read);
    CHECK(ram_sender_index == strlen(ram_sender_query));
    CHECK(strstr(engine_output, "[GC:") != NULL);
    NEAR(ram_arguments[0], 5); NEAR(ram_arguments[1], 7);
}
