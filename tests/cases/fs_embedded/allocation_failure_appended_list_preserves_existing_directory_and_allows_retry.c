#include "support/embedded_allocation_host.h"
int main(void)
{
    fs_embedded_mount(heap_files);
    begin_embedded_heap_failure(1);
    fs_embedded_mount(heap_more);
    end_embedded_heap_failure(1);
    check_embedded_directory(false);
    fs_embedded_mount(heap_more);
    check_embedded_directory(true);
    return EXIT_SUCCESS;
}
