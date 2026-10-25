#include "support/protocol_file_host.h"
#include "fs_ram.h"
static vfs_file_t *plain_job;
static unsigned redirected_ends, provider_ends, plain_reads;
static bool plain_closed;
static int32_t read_plain_job(void)
{
    CHECK(++plain_reads < 1000 && hal.stream.file == plain_job);
    uint8_t c;
    return vfs_read(&c, 1, 1, plain_job) == 1 ? c : ASCII_EOF;
}
static status_code_t redirect_finished(vfs_file_t *file, status_code_t status)
{
    CHECK(file == &fixture_file && status == Status_OK);
    CHECK(gc_state.modal.distance_incremental);
    redirected_ends++;
    stream_redirect_close(file);
    return status;
}
static status_code_t provider_finished(vfs_file_t *file, status_code_t status)
{
    CHECK(status == Status_OK);
    if(++provider_ends == 1) {
        CHECK(file == &fixture_file && file_closes == 1 && hal.stream.file == NULL);
        plain_job = vfs_open("/ram/job", "r");
        CHECK(plain_job != NULL);
        stream_set_file(plain_job, read_plain_job);
    } else {
        CHECK(provider_ends == 2 && file == plain_job && hal.stream.file == file);
        CHECK(!gc_state.modal.distance_incremental);
        vfs_close(file);
        plain_closed = true;
        stream_set_file(NULL, protocol_sender_read);
    }
    return status;
}
int main(void)
{
    prepare_file_stream("G91\n");
    fs_ram_mount();
    vfs_file_t *upload = vfs_open("/ram/job", "w");
    CHECK(upload != NULL && vfs_write("G90\n", 1, 4, upload) == 4);
    vfs_close(upload);
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
    grbl.on_file_end = provider_finished;
    CHECK(stream_redirect_read("/fixture/program", protocol_file_error, redirect_finished));
    CHECK(!protocol_main_loop());
    CHECK(redirected_ends == 1 && provider_ends == 2 && plain_closed && file_closes == 1);
    CHECK(plain_reads == 5 && protocol_file_errors == 0);
    CHECK(!gc_state.modal.distance_incremental && !gc_state.modal.units_imperial);
    CHECK(hal.stream.file == NULL && hal.stream.read == protocol_sender_read);
    CHECK(protocol_sender_index == strlen(protocol_sender_query));
    CHECK(strstr(engine_output, "[GC:") && strstr(engine_output, "G90"));
    CHECK(vfs_unmount(NULL, "/ram"));
    return EXIT_SUCCESS;
}
