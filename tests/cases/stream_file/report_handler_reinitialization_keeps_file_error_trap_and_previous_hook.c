#include "support/file_stream_host.h"
static unsigned init_calls, error_calls;
static void previous_init(void) { init_calls++; }
static status_code_t file_error(status_code_t status) { error_calls++; return status; }
int main(void)
{
    prepare_file_stream("G999");
    grbl.on_report_handlers_init = previous_init;
    vfs_file_t *file = stream_redirect_read("/fixture/program", file_error, NULL);
    CHECK(file != NULL);
    report_init_fns();
    CHECK(init_calls == 1);
    CHECK(grbl.report.status_message(Status_GcodeUnsupportedCommand) == Status_GcodeUnsupportedCommand);
    CHECK(error_calls == 1);
    stream_redirect_close(file);
    return EXIT_SUCCESS;
}
