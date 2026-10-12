#include "support/engine_host.h"
#include "stream.h"
#include "state_machine.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    const io_stream_t *stream = stream_null_init(115200);
    CHECK(stream->get_rx_buffer_count() == 0);
    CHECK(stream->get_tx_buffer_count() == 0);
    return EXIT_SUCCESS;
}
