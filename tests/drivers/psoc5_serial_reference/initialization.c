#include "psoc_host.h"
int main(void)
{
    psoc_start();
    CHECK(psoc_stream->type == StreamType_Serial && psoc_stream->is_connected());
    CHECK(psoc_stream->get_rx_buffer_count() == 0 && psoc_stream->read() == SERIAL_NO_DATA);
    return 0;
}
