#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    ppi_core_handles = true;
    stepper_pulse_start_ptr original = hal.stepper.pulse_start;
    ppi_command(LaserPPI_Rate, 254, STATE_IDLE);
    ppi_command(LaserPPI_Enable, 1, STATE_IDLE);
    CHECK(ppi_core_rate == 254 && ppi_core_width == 1500 && hal.stepper.pulse_start == original);
    ppi_move(100, 1000);
    CHECK(ppi_steps == 100 && !ppi_pulses);
    return 0;
}
