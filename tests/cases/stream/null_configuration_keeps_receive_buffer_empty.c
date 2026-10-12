#include "support/engine_host.h"
#include "stream.h"
#include "protocol.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    const io_stream_t *stream = stream_null_init(115200);
    CHECK(stream->disable_rx(true));
    CHECK(stream->suspend_read(true));
    CHECK(stream->set_baud_rate(921600));
    CHECK(stream->disable_rx(false));
    CHECK(stream->suspend_read(false));
    stream->reset_read_buffer();
    stream->cancel_read_buffer();
    stream->reset_write_buffer();
    CHECK(stream->read() == SERIAL_NO_DATA);
    CHECK(stream->get_rx_buffer_count() == 0);
    CHECK(stream->get_rx_buffer_free() == RX_BUFFER_SIZE);
    return EXIT_SUCCESS;
}
