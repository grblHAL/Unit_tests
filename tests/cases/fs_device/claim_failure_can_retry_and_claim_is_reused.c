#include "support/device_filesystem_host.h"

int main(void)
{
    prepare_device_filesystem();
    device_claim_fails = true;
    CHECK(vfs_open("/dev/uart2", "w") == NULL);
    CHECK(device_claims == 1);
    device_claim_fails = false;
    vfs_file_t *file = vfs_open("/dev/uart2", "w");
    CHECK(file != NULL && device_claims == 2);
    backend_close(file);
    file = vfs_open("/dev/uart2", "w");
    CHECK(file != NULL && device_claims == 2);
    backend_close(file);
    return EXIT_SUCCESS;
}
