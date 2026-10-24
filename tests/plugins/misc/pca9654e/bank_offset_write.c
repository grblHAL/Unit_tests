#include "pca_host.h"
int main(void)
{
    pin_base = 2;
    start_expander();
    xbar_t *pin = outputs.get_pin_info(Port_Output, 0);
    CHECK(pin->id == 0 && pin->pin == 2);
    pin->set_value(pin, 1);
    CHECK(register_values[1] == 1);
    return 0;
}
