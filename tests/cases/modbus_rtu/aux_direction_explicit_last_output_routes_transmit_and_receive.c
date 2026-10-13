#include "support/rtu_aux_direction_host.h"

int main(void)
{
    prepare_rtu_aux_direction(1);
    CHECK(digital_pins[Port_Output][1].mode.claimed);
    CHECK(digital_pins[Port_Output][1].function == Output_RS485_Direction);
    verify_aux_direction_exchange(1);
    return EXIT_SUCCESS;
}
