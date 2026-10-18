#include "support/embedded_allocation_host.h"
int main(void)
{
    fs_embedded_mount(heap_files);
    begin_embedded_heap_failure(1);
    vfs_file_t *file = vfs_open("/embedded/first", "r");
    end_embedded_heap_failure(1);
    CHECK(file == NULL);
    file = vfs_open("/embedded/first", "r");
    CHECK(file != NULL);
    char data = 0;
    CHECK(vfs_read(&data, 1, 1, file) == 1 && data == 'a');
    vfs_close(file);
    check_embedded_directory(false);
    return EXIT_SUCCESS;
}
