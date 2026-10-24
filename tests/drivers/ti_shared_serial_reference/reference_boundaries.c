#include "reference_host.h"
io_stream_details_t *reference_streams;
void stream_register_streams(io_stream_details_t *details)
{
    CHECK(details && details->n_streams == 1 && !reference_streams);
    reference_streams = details;
}
bool stream_connected(void) { return true; }
bool stream_rx_suspend(stream_rx_buffer_t *buffer, bool suspend)
{
    (void)buffer;
    (void)suspend;
    CHECK(false);
    return false;
}
