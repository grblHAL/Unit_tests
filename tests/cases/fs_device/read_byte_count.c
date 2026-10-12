#include "support/engine_host.h"
#include "support/backend_close.h"
#include "stream.h"
#include "check.h"
#include <string.h>
bool device_fs_add_stream(io_stream_properties_t *stream);
void fs_device_mount(void);
static unsigned consumed;
static uint16_t available(void) { return 3 - consumed; }
static int32_t read_byte(void)
{
    CHECK(consumed < 3);
    return "abc"[consumed++];
}
static const io_stream_t *claim(uint32_t baud)
{
    static const io_stream_t stream = {.read = read_byte, .get_rx_buffer_count = available};
    CHECK(baud == 115200);
    return &stream;
}
int main(void)
{
    engine_prepare();
    io_stream_properties_t stream = {.type = StreamType_Serial, .instance = 2, .claim = claim};
    stream.flags.claimable = stream.flags.modbus_ready = true;
    CHECK(device_fs_add_stream(&stream));
    fs_device_mount();
    vfs_file_t *file = vfs_open("/dev/uart2", "w+");
    CHECK(file != NULL);
    char buffer[4] = {0};
    size_t count = vfs_read(buffer, 1, 3, file);
    CHECK(strcmp(buffer, "abc") == 0);
    CHECK(vfs_eof(file));
    backend_close(file);
    fprintf(stderr, "Read byte count: %zu (expected 3)\n", count);
    CHECK(count == 3);
    return EXIT_SUCCESS;
}
