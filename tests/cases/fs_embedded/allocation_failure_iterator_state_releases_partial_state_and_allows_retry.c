#include "support/embedded_allocation_host.h"
int main(void)
{
    fs_embedded_mount(heap_files);
    begin_embedded_heap_failure(1);
    vfs_dir_t *dir = vfs_opendir("/embedded");
    end_embedded_heap_failure(1);
    CHECK(dir == NULL);
    check_embedded_directory(false);
    return EXIT_SUCCESS;
}
