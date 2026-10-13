#include "support/rtu_aux_direction_host.h"

int main(void)
{
    prepare_rtu_aux_direction(0);
    CHECK(digital_pins[Port_Output][0].mode.claimed);
    CHECK(digital_pins[Port_Output][0].function == Output_RS485_Direction);
    verify_aux_direction_exchange(0);
    return EXIT_SUCCESS;
}
