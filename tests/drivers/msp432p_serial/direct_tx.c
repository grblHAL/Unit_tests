#include "msp_host.h"
int main(void)
{
    msp_start();
    CHECK(msp_stream->write_char('A'));
    CHECK(EUSCI_A0->TXBUF == 'A' && !(EUSCI_A0->IE & EUSCI_A_IE_TXIE));
    CHECK(msp_stream->write_char(0xFF));
    CHECK(EUSCI_A0->TXBUF == 0xFF);
    return 0;
}
