#include "support/embedded_allocation_host.h"
#include "support/mount_result_host.h"
static const embedded_file_t heap_second = {.name = "second", .size = 1, .data = {'b'}};
static const embedded_file_t *heap_more[] = {&heap_second, NULL};
int main(void)
{
    CHECK_MOUNT_RESULT(fs_embedded_mount(heap_files), true);
    begin_embedded_heap_failure(1);
    CHECK_MOUNT_RESULT(fs_embedded_mount(heap_more), false);
    end_embedded_heap_failure(1);
    check_embedded_directory(false);
    CHECK_MOUNT_RESULT(fs_embedded_mount(heap_more), true);
    check_embedded_directory(true);
    return EXIT_SUCCESS;
}
