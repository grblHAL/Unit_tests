#include "psoc_host.h"
int main(void)
{
    psoc_start();
    for (unsigned batch = 0; batch < 8; batch++)
    {
        uint8_t data[19];
        for (unsigned i = 0; i < sizeof(data); i++)
            data[i] = 'A' + (batch + i) % 26;
        psoc_receive(data, sizeof(data));
        for (unsigned i = 0; i < sizeof(data); i++)
            CHECK(psoc_stream->read() == data[i]);
        CHECK(psoc_stream->read() == SERIAL_NO_DATA);
    }
    return 0;
}
