#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    stepper_pulse_start_ptr original = hal.stepper.pulse_start;
    ppi_command(LaserPPI_Enable, 1, STATE_CHECK_MODE);
    CHECK(hal.stepper.pulse_start == original && ppi_core_rate == 0);
    ppi_command(LaserPPI_Rate, 254, STATE_CHECK_MODE);
    ppi_command(LaserPPI_Enable, 1, STATE_IDLE);
    CHECK(ppi_core_rate == 600);
    return 0;
}
