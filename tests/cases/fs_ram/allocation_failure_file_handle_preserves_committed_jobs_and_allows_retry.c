#include "support/ram_file_allocation_host.h"

static void reject_next_file_handle(const char *path, const char *mode)
{
    allocation_heap_calls = allocation_heap_failures = allocation_heap_frees = 0;
    allocation_heap_reject = 1;
    observe_allocation_heap = true;
    vfs_file_t *file = vfs_open(path, mode);
    observe_allocation_heap = false;
    CHECK(file == NULL && allocation_heap_calls == 1 && allocation_heap_failures == 1);
    CHECK(allocation_heap_frees == 0);
    for(unsigned i = 0; i < 4; i++) CHECK(allocation_heap_allocations[i] == NULL);
}
int main(void)
{
    prepare_ram_file_allocation();
    reject_next_file_handle("/ram/job", "w");
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/ram/job", &st) == -1);
    vfs_file_t *file = vfs_open("/ram/job", "w");
    CHECK(file != NULL);
    CHECK(vfs_write(ram_program, 1, ram_program_length, file) == ram_program_length);
    vfs_close(file);
    file = vfs_open("/ram/next", "w");
    CHECK(file != NULL && vfs_write("G90\n", 1, 4, file) == 4);
    vfs_close(file);
    reject_next_file_handle("/ram/job", "r");
    CHECK(vfs_stat("/ram/job", &st) == 0 && st.st_size == ram_program_length);
    CHECK(vfs_stat("/ram/next", &st) == 0 && st.st_size == 4);
    file = vfs_open("/ram/job", "r");
    CHECK(file != NULL);
    char received[sizeof(ram_program)];
    CHECK(vfs_read(received, 1, sizeof(received), file) == ram_program_length);
    CHECK(memcmp(received, ram_program, ram_program_length) == 0 && vfs_eof(file));
    vfs_close(file);
    file = vfs_open("/ram/next", "r");
    CHECK(file != NULL && vfs_read(received, 1, sizeof(received), file) == 4);
    CHECK(memcmp(received, "G90\n", 4) == 0);
    vfs_close(file);
    CHECK(vfs_open("/ram/job", "r") == NULL && vfs_open("/ram/next", "r") == NULL);
    check_new_ram_job_can_be_written_and_read();
    return EXIT_SUCCESS;
}
