#include "stmh7_serial_host.h"
int main(void)
{
    stmh7_prepare();
    const char line[] = "G1X10F200\n";
    for (const char *s = line; *s; s++)
        stmh7_receive(*s);
    CHECK(stmh7_stream->get_rx_buffer_count() == sizeof(line) - 1);
    for (const char *s = line; *s; s++)
        CHECK(stmh7_stream->read() == *s);
    CHECK(stmh7_stream->read() == SERIAL_NO_DATA && stmh7_rt_calls == sizeof(line) - 1);
    return 0;
}
