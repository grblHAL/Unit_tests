#include "pca_host.h"
int main(void)
{
    start_expander();
    CHECK(outputs.get_pin_info(Port_Input, 0) == NULL);
    CHECK(outputs.get_pin_info(Port_Output, 8) == NULL);
    outputs.digital_out(8, true);
    outputs.set_pin_description(Port_Input, 0, "Ignore");
    outputs.set_pin_description(Port_Output, 8, "Ignore");
    CHECK(writes == 3 && register_values[1] == 0);
    xbar_t *pin = outputs.get_pin_info(Port_Output, 7);
    pin->set_value(pin, 1);
    CHECK(writes == 4 && register_values[1] == 128 && pin->get_value(pin) == 1);
    pin->set_value(pin, 0);
    CHECK(writes == 5 && register_values[1] == 0 && pin->get_value(pin) == 0);
    return 0;
}
