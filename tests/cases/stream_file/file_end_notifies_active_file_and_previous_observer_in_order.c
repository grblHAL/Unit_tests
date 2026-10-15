#include "support/file_stream_host.h"
static unsigned calls;
static vfs_file_t *expected_file;
static status_code_t active_end(vfs_file_t *file, status_code_t status)
{ CHECK(file == expected_file && status == Status_OK); CHECK(calls++ == 0); return status; }
static status_code_t previous_end(vfs_file_t *file, status_code_t status)
{ CHECK(file == expected_file && status == Status_OK); CHECK(calls++ == 1); return status; }
int main(void)
{
    prepare_file_stream("M2");
    grbl.on_file_end = previous_end;
    expected_file = stream_redirect_read("/fixture/program", NULL, active_end);
    CHECK(expected_file != NULL);
    CHECK(grbl.on_file_end(expected_file, Status_OK) == Status_OK);
    CHECK(calls == 2);
    stream_redirect_close(expected_file);
    return EXIT_SUCCESS;
}
