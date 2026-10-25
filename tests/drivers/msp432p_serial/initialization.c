#include "msp_host.h"
int main(void)
{
    msp_start();
    CHECK(pins == 2 && cpu_enabled && irq_enables == 1);
    CHECK(P1->SEL0 == ((1U << 2) | (1U << 3)));
    CHECK(NVIC_GetPriority(EUSCIA0_IRQn) == 3);
    CHECK(NVIC->ISER[(unsigned)EUSCIA0_IRQn >> 5] & (1U << ((unsigned)EUSCIA0_IRQn & 31)));
    CHECK(EUSCI_A0->BRW == 6 && EUSCI_A0->MCTLW == ((0x20U << 8) | (8U << 4) | 1U));
    CHECK(msp_stream->get_rx_buffer_free() == 31 && msp_stream->read() == SERIAL_NO_DATA &&
          cpu_enabled);
    return 0;
}
