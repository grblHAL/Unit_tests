#include "msp_host.h"
int main(void)
{
    msp_start();
    msp_busy(true);
    msp_stream->write("G1X10");
    CHECK(EUSCI_A0->IE & EUSCI_A_IE_TXIE);
    msp_drain();
    CHECK(sent_count == 5 && memcmp(sent, "G1X10", 5) == 0 && !(EUSCI_A0->IE & EUSCI_A_IE_TXIE));
    return 0;
}
