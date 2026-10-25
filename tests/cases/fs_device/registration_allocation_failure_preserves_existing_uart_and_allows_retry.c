#include "support/device_filesystem_host.h"
#include "support/calloc_failure_host.h"

int main(void)
{
    prepare_device_filesystem();
    io_stream_properties_t second = {.type = StreamType_Serial, .instance = 3, .claim = device_claim};
    second.flags.claimable = second.flags.modbus_ready = true;
    fail_calloc = true;
    bool registered = device_fs_add_stream(&second);
    fail_calloc = false;
    CHECK(!registered && failed_calloc_calls == 1);
    CHECK(device_claims == 0);
    CHECK(vfs_open("/dev/uart3", "w") == NULL);
    vfs_file_t *first = vfs_open("/dev/uart2", "w");
    CHECK(first != NULL && device_claims == 1);
    CHECK(vfs_write("old", 1, 3, first) == 3);
    vfs_close(first);
    CHECK(device_fs_add_stream(&second));
    vfs_file_t *retry = vfs_open("/dev/uart3", "w");
    CHECK(retry != NULL && device_claims == 2);
    CHECK(vfs_write("new", 1, 3, retry) == 3);
    vfs_close(retry);
    CHECK(failed_calloc_calls == 1);
    return EXIT_SUCCESS;
}
