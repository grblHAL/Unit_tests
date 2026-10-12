#include "support/device_filesystem_host.h"

int main(void)
{
    prepare_device_filesystem();
    register_device(StreamType_Bluetooth, 1);
    vfs_file_t *serial = vfs_open("/dev/uart2", "w");
    vfs_file_t *bluetooth = vfs_open("/dev/bt1", "w");
    CHECK(serial != NULL && bluetooth != NULL);
    CHECK(device_claims == 2);
    CHECK(vfs_open("/dev/bt1", "w") == NULL);
    CHECK(vfs_open("/dev/uart2", "w") == NULL);
    backend_close(bluetooth);
    CHECK(vfs_open("/dev/uart2", "w") == NULL);
    bluetooth = vfs_open("/dev/bt1", "w");
    CHECK(bluetooth != NULL && device_claims == 2);
    backend_close(bluetooth);
    backend_close(serial);
    return EXIT_SUCCESS;
}
