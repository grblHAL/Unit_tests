#include "pca_host.h"
int main(void)
{
    start_expander();
    CHECK(starts == 1 && probes == 1 && writes == 3 && registrations == 1);
    CHECK(enumerations == 1 && register_values[1] == 0 && register_values[2] == 0 &&
          register_values[3] == 0);
    for (unsigned i = 0; i < 8; i++)
    {
        xbar_t *pin = outputs.get_pin_info(Port_Output, i);
        CHECK(pin && pin->id == i && pin->pin == i && pin->function == Output_Aux2 + i);
        CHECK(pin->cap.output && pin->cap.external && pin->cap.claimable && pin->mode.output);
        CHECK(pin->get_value(pin) == 0);
    }
    return 0;
}
