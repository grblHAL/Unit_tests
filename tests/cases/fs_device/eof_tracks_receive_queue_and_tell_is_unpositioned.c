#include "support/device_filesystem_host.h"

int main(void)
{
    prepare_device_filesystem();
    vfs_file_t *file = vfs_open("/dev/uart2", "w");
    CHECK(file != NULL);
    CHECK(vfs_tell(file) == 0);
    CHECK(vfs_eof(file));
    device_pending = 2;
    CHECK(!vfs_eof(file));
    CHECK(vfs_write("abc", 1, 3, file) == 3);
    CHECK(vfs_tell(file) == 0);
    device_pending = 0;
    CHECK(vfs_eof(file));
    backend_close(file);
    return EXIT_SUCCESS;
}
