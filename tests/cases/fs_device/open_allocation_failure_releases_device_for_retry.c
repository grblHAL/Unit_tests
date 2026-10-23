#include "support/device_filesystem_host.h"
#include "support/calloc_failure_host.h"

int main(void)
{
    prepare_device_filesystem();
    register_device(StreamType_Serial, 3);
    fail_calloc = true;
    vfs_file_t *failed = vfs_open("/dev/uart2", "w");
    fail_calloc = false;
    CHECK(failed == NULL && failed_calloc_calls == 1);
    CHECK(device_claims == 1);
    vfs_file_t *retry = vfs_open("/dev/uart2", "w");
    if(retry) {
        CHECK(vfs_write("retry", 1, 5, retry) == 5);
        vfs_close(retry);
    }
    CHECK(device_claims == 1);
    vfs_file_t *other = vfs_open("/dev/uart3", "w");
    CHECK(other != NULL && device_claims == 2);
    CHECK(vfs_write("other", 1, 5, other) == 5);
    vfs_close(other);
    CHECK(failed_calloc_calls == 1);
    fprintf(stderr, "Device open after allocation recovery: %s\n", retry ? "available" : "still reserved");
    CHECK(retry != NULL);
    return EXIT_SUCCESS;
}
