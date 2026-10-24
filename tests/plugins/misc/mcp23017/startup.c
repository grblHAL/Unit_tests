#include "mcp_host.h"
int main(void)
{
    start_mcp();
    CHECK(starts == 1 && probes == 1 && registrations == 1 && writes == 3 && gpio == 0);
    for (unsigned i = 0; i < 16; i++)
    {
        xbar_t *pin = bank.get_pin_info(Port_Output, i);
        CHECK(pin && pin->id == i && pin->function == Output_Aux2 + i);
        CHECK(pin->cap.output && pin->cap.external && pin->cap.claimable && pin->mode.output);
        CHECK(pin->get_value(pin) == 0);
    }
    CHECK(bank.get_pin_info(Port_Input, 0) == NULL && bank.get_pin_info(Port_Output, 16) == NULL);
    bank.digital_out(16, true);
    CHECK(writes == 3);
    return 0;
}
