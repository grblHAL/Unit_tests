#include "msp_host.h"
int main(void)
{
    msp_start();
    msp_busy(true);
    msp_stream->write("G1");
    CHECK(EUSCI_A0->IE & EUSCI_A_IE_TXIE);
    CHECK(msp_stream->disable_rx(true));
    CHECK(!(EUSCI_A0->IE & EUSCI_A_IE_RXIE));
    CHECK(EUSCI_A0->IE & EUSCI_A_IE_TXIE);
    CHECK(msp_stream->disable_rx(false));
    msp_drain();
    CHECK(sent_count == 2 && memcmp(sent, "G1", 2) == 0);
    return 0;
}
