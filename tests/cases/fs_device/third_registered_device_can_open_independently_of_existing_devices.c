#include "support/device_filesystem_host.h"
int main(void)
{
    prepare_device_filesystem();
    register_device(StreamType_Bluetooth, 1);
    register_device(StreamType_Serial, 3);
    vfs_file_t *first = vfs_open("/dev/uart2", "w");
    vfs_file_t *second = vfs_open("/dev/bt1", "w");
    vfs_file_t *third = vfs_open("/dev/uart3", "w");
    CHECK(first && second && third && device_claims == 3);
    CHECK(vfs_write("third", 1, 5, third) == 5);
    CHECK(vfs_open("/dev/uart3", "w") == NULL);
    backend_close(third);
    third = vfs_open("/dev/uart3", "w");
    CHECK(third && device_claims == 3);
    CHECK(vfs_open("/dev/uart2", "w") == NULL);
    backend_close(first); backend_close(second); backend_close(third);
    return EXIT_SUCCESS;
}
