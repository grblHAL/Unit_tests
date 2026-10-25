#include "stm_serial_host.h"
int main(void)
{
    stm_serial_prepare();
    const char line[] = "G1X10F200\n";
    for (const char *s = line; *s; s++)
        stm_receive(*s);
    CHECK(stm_stream->get_rx_buffer_count() == sizeof(line) - 1);
    for (const char *s = line; *s; s++)
        CHECK(stm_stream->read() == *s);
    CHECK(stm_stream->read() == SERIAL_NO_DATA && stm_rt_calls == sizeof(line) - 1);
    return 0;
}
