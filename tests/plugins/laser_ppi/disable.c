#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    stepper_pulse_start_ptr original = hal.stepper.pulse_start;
    ppi_command(LaserPPI_Enable, 1, STATE_IDLE);
    CHECK(hal.stepper.pulse_start != original && ppi_core_rate == 600);
    ppi_motor->update_rpm(ppi_motor, 500);
    ppi_move(1, 1000);
    CHECK(ppi_pulses == 1);
    ppi_command(LaserPPI_Enable, 0, STATE_IDLE);
    CHECK(hal.stepper.pulse_start == original && ppi_core_rate == 0);
    ppi_move(100, 1000);
    CHECK(ppi_pulses == 1 && ppi_steps == 101);
    return 0;
}
