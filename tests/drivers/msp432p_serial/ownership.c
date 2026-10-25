#include "msp_host.h"
int main(void)
{
    msp_start();
    CHECK(!stream_open_instance(0, 115200, NULL, NULL));
    CHECK(stream_close(msp_stream));
    CHECK(!stream_close(msp_stream));
    CHECK(!stream_open_instance(0, 57600, NULL, NULL));
    const io_stream_t *again = stream_open_instance(0, 115200, NULL, NULL);
    CHECK(again == msp_stream && pins == 2 && irq_enables == 1);
    return 0;
}
