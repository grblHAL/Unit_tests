#include "support/ram_file_allocation_host.h"
int main(void)
{
    prepare_ram_file_allocation();
    vfs_file_t *file = vfs_open("/ram/job", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("G1X1\nG1X2\n", 1, 10, file) == 10);
    vfs_close(file);
    file = vfs_open("/ram/job", "r");
    CHECK(file != NULL);
    fail_realloc = true;
    CHECK(vfs_truncate(file, 5) == -1);
    fail_realloc = false;
    CHECK(failed_realloc_calls == 1);
    vfs_close(file);
    CHECK(vfs_open("/ram/job", "r") == NULL);
    check_new_ram_job_can_be_written_and_read();
    return EXIT_SUCCESS;
}
