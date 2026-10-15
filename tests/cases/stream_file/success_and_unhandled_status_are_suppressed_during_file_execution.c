#include "support/file_stream_host.h"
static unsigned calls;
static status_code_t file_status(status_code_t status) { calls++; return status; }
int main(void)
{
    prepare_file_stream("G0X1");
    vfs_file_t *file = stream_redirect_read("/fixture/program", file_status, NULL);
    CHECK(file != NULL);
    CHECK(grbl.report.status_message(Status_OK) == Status_OK);
    CHECK(grbl.report.status_message(Status_Unhandled) == Status_Unhandled);
    CHECK(calls == 0 && engine_output[0] == '\0');
    CHECK(gc_state.last_error == Status_Unhandled);
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
