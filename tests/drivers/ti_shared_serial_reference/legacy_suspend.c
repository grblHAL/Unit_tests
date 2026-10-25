#include "reference_host.h"
static unsigned acknowledgements;
static void acknowledged(void) { acknowledgements++; }
int main(void)
{
    uart_start();
    CHECK(stream_get_flags(*uart_stream).claimed);
    CHECK(stream_connect(uart_stream));
    grbl.on_toolchange_ack = acknowledged;
    uart_receive('G');
    uart_receive('1');
    CHECK(uart_stream->suspend_read(true) && hal.stream.read() == SERIAL_NO_DATA);
    uart_receive(CMD_TOOL_ACK);
    fprintf(stderr, "Tool acknowledgements=%u\n", acknowledgements);
    CHECK(acknowledgements == 1);
    uart_receive('X');
    CHECK(hal.stream.read() == 'X' && hal.stream.read() == SERIAL_NO_DATA);
    CHECK(uart_stream->suspend_read(false));
    CHECK(hal.stream.read() == 'G' && hal.stream.read() == '1' &&
          hal.stream.read() == SERIAL_NO_DATA);
    uart_receive('Y');
    CHECK(hal.stream.read() == 'Y' && acknowledgements == 1);
    return 0;
}
