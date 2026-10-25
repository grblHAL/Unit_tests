#include "stm7_serial_host.h"
int main(void)
{
    stm7_prepare();
    const char line[] = "G1X10F200\n";
    for (const char *s = line; *s; s++)
        stm7_receive(*s);
    CHECK(stm7_stream->get_rx_buffer_count() == sizeof(line) - 1);
    for (const char *s = line; *s; s++)
        CHECK(stm7_stream->read() == *s);
    CHECK(stm7_stream->read() == SERIAL_NO_DATA && stm7_rt_calls == sizeof(line) - 1);
    return 0;
}
