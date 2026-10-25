#include "stm3_serial_host.h"
int main(void)
{
    stm3_prepare();
    for (unsigned round = 0; round < 3; round++)
    {
        for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
            stm3_receive('A' + i % 26);
        stm3_receive('z');
        for (unsigned i = 0; i < RX_BUFFER_SIZE - 1; i++)
            CHECK(stm3_stream->read() == 'A' + (int)(i % 26));
        CHECK(stm3_stream->read() == SERIAL_NO_DATA);
    }
    return 0;
}
