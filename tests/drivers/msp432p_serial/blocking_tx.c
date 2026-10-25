#include "msp_host.h"
int main(void)
{
    msp_start();
    msp_busy(true);
    allow_blocking = true;
    for (unsigned i = 0; i < 50; i++)
        CHECK(msp_stream->write_char('A' + i % 20));
    msp_drain();
    CHECK(sent_count == 50 && blocks > 0);
    for (unsigned i = 0; i < 50; i++)
        CHECK(sent[i] == 'A' + i % 20);
    return 0;
}
