#include "spi_host.h"
int main(void)
{
    start_hc595();
    CHECK(starts == 1 && registrations == 1 && selections == 0 && transfers == 0);
    for (unsigned i = 0; i < HC595_ENABLE * 8; i++)
    {
        xbar_t *pin = bank.get_pin_info(Port_Output, i);
        CHECK(pin && pin->id == i && pin->pin == i && pin->function == Output_Aux2 + i);
        CHECK(pin->ports_id == bank.ports && pin->cap.external && pin->cap.output &&
              pin->cap.claimable);
        CHECK(pin->get_value(pin) == 0);
    }
    CHECK(bank.get_pin_info(Port_Input, 0) == NULL);
    CHECK(bank.get_pin_info(Port_Output, HC595_ENABLE * 8) == NULL);
    bank.digital_out(HC595_ENABLE * 8, true);
    CHECK(transfers == 0);
    return 0;
}
