#include "stm1_serial_host.h"
int main(void)
{
    stm1_prepare();
    const char line[] = "G1X10F200\n";
    for (const char *s = line; *s; s++)
        stm1_receive(*s);
    for (const char *s = line; *s; s++)
        CHECK(stm1_stream->read() == *s);
    CHECK(stm1_stream->read() == SERIAL_NO_DATA && stm1_rt_calls == sizeof(line) - 1);
    return 0;
}
