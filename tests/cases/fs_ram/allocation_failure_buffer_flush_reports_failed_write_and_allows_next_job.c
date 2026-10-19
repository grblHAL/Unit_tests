#include "support/ram_file_allocation_host.h"
int main(void)
{
    prepare_ram_file_allocation();
    vfs_file_t *file = vfs_open("/ram/job", "w");
    CHECK(file != NULL);
    CHECK(vfs_write("G21\n", 1, 4, file) == 4);
    fail_realloc = true;
    CHECK(vfs_write(ram_program, 1, ram_program_length, file) == 0);
    fail_realloc = false;
    CHECK(failed_realloc_calls == 1);
    vfs_close(file);
    /* RAM files are hidden from directory mutation; consuming a reader closes
       and removes the temporary job through the supported public API. */
    file = vfs_open("/ram/job", "r");
    CHECK(file != NULL);
    vfs_close(file);
    CHECK(vfs_open("/ram/job", "r") == NULL);
    check_new_ram_job_can_be_written_and_read();
    return EXIT_SUCCESS;
}
