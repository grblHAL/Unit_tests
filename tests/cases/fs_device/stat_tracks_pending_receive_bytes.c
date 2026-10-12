#include "support/device_filesystem_host.h"

int main(void)
{
    prepare_device_filesystem();
    vfs_file_t *file = vfs_open("/dev/uart2", "w");
    CHECK(file != NULL);
    device_pending = 7;
    vfs_stat_t st = {0};
    CHECK(vfs_stat("/dev/uart2", &st) == 0 && st.st_size == 7);
    device_pending = 0;
    CHECK(vfs_stat("/dev/uart2", &st) == 0 && st.st_size == 0);
    CHECK(vfs_stat("/dev/absent", &st) == -1 && st.st_size == 0);
    backend_close(file);
    return EXIT_SUCCESS;
}
