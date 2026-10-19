#include "support/ram_file_allocation_host.h"
int main(void)
{
    prepare_ram_file_allocation();
    allocation_heap_reject = 2;
    observe_allocation_heap = true;
    vfs_file_t *file = vfs_open("/ram/job", "w");
    observe_allocation_heap = false;
    CHECK(file == NULL && allocation_heap_failures == 1);
    CHECK(allocation_heap_calls == 2 && allocation_heap_frees == 1);
    for(unsigned i = 0; i < 4; i++) CHECK(allocation_heap_allocations[i] == NULL);
    check_new_ram_job_can_be_written_and_read();
    return EXIT_SUCCESS;
}
