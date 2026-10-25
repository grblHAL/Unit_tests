#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    const char line[] = "G1X10F200\n";
    for (const char *s = line; *s; s++)
        stm3_receive(*s);
    for (const char *s = line; *s; s++)
        CHECK(stm3_stream->read() == *s);
    CHECK(stm3_stream->read() == SERIAL_NO_DATA && stm3_rt_calls == sizeof(line) - 1);
    return 0;
}
