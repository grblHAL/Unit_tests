#include "spi_host.h"
int main(void)
{
    start_hc595();
    uint32_t expected = 0;
    for (unsigned i = 0; i < HC595_ENABLE * 8; i++)
    {
        bank.digital_out(i, true);
        expected |= 1u << i;
        CHECK(shifted == expected && transfers == i + 1 && deselections == transfers);
        bank.digital_out(i, true);
        CHECK(transfers == i + 1 && selections == transfers);
    }
    for (unsigned i = 0; i < HC595_ENABLE * 8; i++)
    {
        bank.digital_out(i, false);
        expected &= ~(1u << i);
        CHECK(shifted == expected && deselections == transfers);
        xbar_t *pin = bank.get_pin_info(Port_Output, i);
        CHECK(pin->get_value(pin) == 0);
    }
    CHECK(shifted == 0 && transfers == HC595_ENABLE * 16);
    return 0;
}
