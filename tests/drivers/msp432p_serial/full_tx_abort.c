#include "msp_host.h"
int main(void)
{
    msp_start();
    msp_busy(true);
    for (unsigned i = 0; i < 15; i++)
        CHECK(msp_stream->write_char('A' + i));
    CHECK(!msp_stream->write_char('Z') && blocks == 1);
    msp_drain();
    CHECK(sent_count == 15);
    for (unsigned i = 0; i < 15; i++)
        CHECK(sent[i] == 'A' + i);
    return 0;
}
