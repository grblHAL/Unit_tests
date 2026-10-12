#include "support/engine_host.h"
#include "stream.h"
#include "protocol.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    const io_stream_t *stream = stream_null_init(115200);
    stream->write("ignored");
    uint8_t bytes[] = {'A', 0, 'B'};
    stream->write_n(bytes, sizeof(bytes));
    CHECK(stream->write_char('C'));
    CHECK(engine_output[0] == '\0');
    CHECK(stream->get_tx_buffer_count() == 0);
    CHECK(stream->get_rx_buffer_free() == RX_BUFFER_SIZE);
    return EXIT_SUCCESS;
}
