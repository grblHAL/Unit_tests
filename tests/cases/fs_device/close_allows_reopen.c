#include "support/engine_host.h"
#include "support/backend_close.h"
#include "stream.h"
#include <string.h>
#include "check.h"
bool device_fs_add_stream(io_stream_properties_t *stream);
void fs_device_mount(void);
static unsigned claims;
static char output[16];
static void write_bytes(const uint8_t *data, uint16_t length)
{
    CHECK(length < sizeof(output));
    memcpy(output, data, length);
    output[length] = '\0';
}
static uint16_t rx_count(void) { return 0; }
static const io_stream_t *claim(uint32_t baud)
{
    static const io_stream_t stream = {.write_n = write_bytes, .get_rx_buffer_count = rx_count};
    CHECK(baud == 115200);
    CHECK(output[0] == '\0');
    claims++;
    return &stream;
}
static void prepare_device(void)
{
    engine_prepare();
    io_stream_properties_t stream = {.type = StreamType_Serial, .instance = 2, .claim = claim};
    stream.flags.claimable = stream.flags.modbus_ready = true;
    CHECK(device_fs_add_stream(&stream));
    fs_device_mount();
}

int main(void)
{
    prepare_device();
    vfs_file_t *file = vfs_open("/dev/uart2", "w");
    CHECK(file != NULL);
    backend_close(file);
    file = vfs_open("/dev/uart2", "w");
    CHECK(file != NULL);
    CHECK(claims == 1);
    backend_close(file);
    return EXIT_SUCCESS;
}
