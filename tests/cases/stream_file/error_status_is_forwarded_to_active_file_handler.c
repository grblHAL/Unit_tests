#include "support/file_stream_host.h"
static unsigned calls;
static status_code_t file_status(status_code_t status)
{
    calls++; CHECK(status == Status_GcodeUnsupportedCommand); return status;
}
int main(void)
{
    prepare_file_stream("G999");
    vfs_file_t *file = stream_redirect_read("/fixture/program", file_status, NULL);
    CHECK(file != NULL);
    CHECK(grbl.report.status_message(Status_GcodeUnsupportedCommand) == Status_GcodeUnsupportedCommand);
    CHECK(calls == 1 && gc_state.last_error == Status_GcodeUnsupportedCommand);
    CHECK(hal.stream.file == file);
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
