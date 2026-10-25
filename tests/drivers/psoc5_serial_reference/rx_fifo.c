#include "psoc_host.h"
int main(void)
{
    psoc_start();
    const uint8_t line[] = "G1!X10\n";
    psoc_receive(line, sizeof(line) - 1);
    CHECK(rt_calls == sizeof(line) - 1 && psoc_stream->get_rx_buffer_count() == 6);
    const char *expected = "G1X10\n";
    for (; *expected; expected++)
        CHECK(psoc_stream->read() == *expected);
    CHECK(psoc_stream->read() == SERIAL_NO_DATA);
    return 0;
}
