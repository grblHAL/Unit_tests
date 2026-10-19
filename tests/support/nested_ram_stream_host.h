#pragma once
#include "support/engine_host.h"
#include "fs_ram.h"
#include "stream_file.h"
#include "protocol.h"
#include "state_machine.h"
#include "report.h"
#include "check.h"
#include <string.h>
static vfs_file_t *nested_ram_files[3];
static unsigned nested_status_calls[3], nested_eof_calls[3], nested_prior_eof_calls;
static unsigned nested_event_order, nested_local_order[3], nested_prior_order;
static bool nested_connected(void) { return true; }
static void nested_driver_reset(void) { }
static status_code_t nested_status(unsigned index, status_code_t status)
{
    CHECK(hal.stream.file == nested_ram_files[index]);
    CHECK(status == Status_UserException);
    nested_status_calls[index]++;
    return Status_OK;
}
static status_code_t nested_status0(status_code_t status) { return nested_status(0, status); }
static status_code_t nested_status1(status_code_t status) { return nested_status(1, status); }
static status_code_t nested_status2(status_code_t status) { return nested_status(2, status); }
static status_code_t nested_eof(unsigned index, vfs_file_t *file, status_code_t status)
{
    CHECK(file == nested_ram_files[index] && status == Status_OK);
    nested_eof_calls[index]++;
    nested_local_order[index] = ++nested_event_order;
    return status;
}
static status_code_t nested_eof0(vfs_file_t *file, status_code_t status) { return nested_eof(0, file, status); }
static status_code_t nested_eof1(vfs_file_t *file, status_code_t status) { return nested_eof(1, file, status); }
static status_code_t nested_eof2(vfs_file_t *file, status_code_t status) { return nested_eof(2, file, status); }
static status_code_t nested_previous_eof(vfs_file_t *file, status_code_t status)
{
    CHECK(file == hal.stream.file && status == Status_OK);
    nested_prior_eof_calls++;
    nested_prior_order = ++nested_event_order;
    return status;
}
static void nested_expect_text(const char *text)
{
    while(*text) CHECK(hal.stream.read() == (uint8_t)*text++);
}
static void nested_create_file(const char *path, const char *text)
{
    vfs_file_t *file = vfs_open(path, "w");
    CHECK(file != NULL);
    CHECK(vfs_write(text, 1, strlen(text), file) == strlen(text));
    vfs_close(file);
}
static inline void prepare_ram_stream_environment(void)
{
    engine_parser_prepare();
    hal.driver_reset = nested_driver_reset;
    hal.stream.read = stream_get_null;
    hal.stream.is_connected = nested_connected;
    report_init_fns(); report_init(); state_set(STATE_IDLE);
    fs_ram_mount();
}
static inline void prepare_nested_ram_streams(void)
{
    prepare_ram_stream_environment();
    grbl.on_file_end = nested_previous_eof;
    nested_create_file("/ram/main", "G90\nG91\n");
    nested_create_file("/ram/sub", "F100\nF200\n");
    nested_create_file("/ram/leaf", "G21\n");
    const char *paths[] = {"/ram/main", "/ram/sub", "/ram/leaf"};
    const char *lines[] = {"G90\n", "F100\n", "G21\n"};
    status_message_ptr statuses[] = {nested_status0, nested_status1, nested_status2};
    on_file_end_ptr endings[] = {nested_eof0, nested_eof1, nested_eof2};
    for(unsigned i = 0; i < 3; i++) {
        nested_ram_files[i] = stream_redirect_read(paths[i], statuses[i], endings[i]);
        CHECK(nested_ram_files[i] != NULL && hal.stream.file == nested_ram_files[i]);
        CHECK(stream_is_file());
        nested_expect_text(lines[i]);
        CHECK(grbl.on_line_number_assigned(0) == 1);
    }
}
static inline void close_nested_ram_level(unsigned index)
{
    CHECK(hal.stream.file == nested_ram_files[index]);
    stream_redirect_close(nested_ram_files[index]);
    CHECK(hal.stream.file == (index ? nested_ram_files[index - 1] : NULL));
    if(index) CHECK(grbl.on_line_number_assigned(0) == 1);
    else {
        CHECK(hal.stream.read == stream_get_null && !stream_is_file());
        CHECK(hal.stream.read() == SERIAL_NO_DATA);
    }
}
