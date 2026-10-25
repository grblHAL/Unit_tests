#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    stepper_pulse_start_ptr original = hal.stepper.pulse_start;
    ppi_command(LaserPPI_Enable, 1, STATE_IDLE);
    grbl.on_parser_init(&gc_state);
    CHECK(ppi_parser_inits == 1 && hal.stepper.pulse_start == original && ppi_core_rate == 0);
    return 0;
}
