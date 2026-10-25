#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    stepper_pulse_start_ptr original = hal.stepper.pulse_start;
    ppi_command(LaserPPI_Rate, 0, STATE_IDLE);
    ppi_command(LaserPPI_Enable, 1, STATE_IDLE);
    CHECK(hal.stepper.pulse_start == original);
    ppi_command(LaserPPI_Rate, 254, STATE_IDLE);
    CHECK(hal.stepper.pulse_start != original);
    ppi_command(LaserPPI_PulseLength, 0, STATE_IDLE);
    CHECK(hal.stepper.pulse_start == original && ppi_core_rate == 0);
    return 0;
}
