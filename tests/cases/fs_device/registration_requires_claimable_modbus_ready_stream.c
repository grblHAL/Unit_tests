#include "support/device_filesystem_host.h"

int main(void)
{
    engine_prepare();
    io_stream_properties_t stream = {.type = StreamType_Serial, .instance = 3, .claim = device_claim};
    CHECK(!device_fs_add_stream(&stream));
    stream.flags.claimable = true;
    CHECK(!device_fs_add_stream(&stream));
    stream.flags.claimable = false;
    stream.flags.modbus_ready = true;
    CHECK(!device_fs_add_stream(&stream));
    stream.flags.claimable = true;
    CHECK(device_fs_add_stream(&stream));
    fs_device_mount();
    vfs_file_t *file = vfs_open("/dev/uart3", "w");
    CHECK(file != NULL && device_claims == 1);
    backend_close(file);
    return EXIT_SUCCESS;
}
