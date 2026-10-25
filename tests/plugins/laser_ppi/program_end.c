#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    stepper_pulse_start_ptr original = hal.stepper.pulse_start;
    ppi_command(LaserPPI_Enable, 1, STATE_IDLE);
    grbl.on_program_completed(ProgramFlow_CompletedM30, true);
    CHECK(hal.stepper.pulse_start != original);
    grbl.on_program_completed(ProgramFlow_CompletedM30, false);
    CHECK(ppi_completions == 2 && hal.stepper.pulse_start == original && ppi_core_rate == 0);
    return 0;
}
