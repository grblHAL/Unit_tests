#include "flex_host.h"
int main(void)
{
    flex_start();
    CHECK(bank.ports->external && bank.ports->in.n_ports == 5 + N_ABC_MOTORS &&
          bank.ports->out.n_ports == 15 + N_ABC_MOTORS);
    CHECK(sends == 1 && receives == 1 && last_size == 8);
    for (unsigned i = 0; i < bank.ports->out.n_ports; i++)
    {
        xbar_t pin = flex_pin(Port_Output, i);
        CHECK(pin.cap.external && pin.mode.output && pin.function == Output_Aux0 + 3 + i);
    }
    CHECK(bank.get_pin_info(Port_Input, 255) == NULL &&
          bank.get_pin_info(Port_Output, 255) == NULL);
    return 0;
}
