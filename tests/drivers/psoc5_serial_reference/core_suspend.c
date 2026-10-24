#include "psoc_host.h"
static unsigned acknowledgements;
static void acknowledged(void) { acknowledgements++; }
int main(void)
{
    psoc_start();
    CHECK(stream_connect(psoc_stream));
    grbl.on_toolchange_ack = acknowledged;
    const uint8_t queued[] = {'G', '1'};
    psoc_receive(queued, sizeof(queued));
    CHECK(psoc_stream->suspend_read(true) && hal.stream.read() == SERIAL_NO_DATA);
    const uint8_t ack = CMD_TOOL_ACK;
    psoc_receive(&ack, 1);
    CHECK(acknowledgements == 1);
    const uint8_t next = 'X';
    psoc_receive(&next, 1);
    CHECK(hal.stream.read() == 'X' && hal.stream.read() == SERIAL_NO_DATA);
    CHECK(psoc_stream->suspend_read(false));
    CHECK(hal.stream.read() == 'G' && hal.stream.read() == '1' &&
          hal.stream.read() == SERIAL_NO_DATA);
    return 0;
}
