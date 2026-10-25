#include "msp_host.h"
int main(void)
{
    msp_start();
    CHECK(msp_stream->disable_rx(true));
    CHECK(EUSCI_A0->IE == 0);
    CHECK(msp_stream->disable_rx(false));
    CHECK(EUSCI_A0->IE == EUSCI_A_IE_RXIE);
    msp_receive('G');
    CHECK(msp_stream->read() == 'G');
    return 0;
}
