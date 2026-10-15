#include "support/multi_bank_ioports_host.h"
int main(void)
{
    prepare_multi_bank_ioports();
    CHECK(bank_digital_data[1].in.pin_base == 0 && bank_digital_data[1].out.pin_base == 0);
    CHECK(bank_digital_data[2].in.pin_base == 2 && bank_digital_data[2].out.pin_base == 2);
    xbar_t *pin = ioport_get_info(Port_Digital, Port_Input, 4);
    CHECK(pin && pin->ports_id == &bank_digital_data[2]);
    CHECK(pin->id == 0);
    return EXIT_SUCCESS;
}
