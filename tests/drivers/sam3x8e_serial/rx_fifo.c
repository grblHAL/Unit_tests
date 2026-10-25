#include "sam_host.h"
int main(void)
{
    sam_prepare();
    const char *lines[] = {"G1X10\n", "$I\n"};
    for (unsigned n = 0; n < 2; n++)
    {
        for (const char *s = lines[n]; *s; s++)
            sam_receive(n, *s);
        CHECK(sam_stream[n]->get_rx_buffer_count() == strlen(lines[n]));
        for (const char *s = lines[n]; *s; s++)
            CHECK(sam_stream[n]->read() == *s);
        CHECK(sam_stream[n]->read() == SERIAL_NO_DATA);
    }
    return 0;
}
