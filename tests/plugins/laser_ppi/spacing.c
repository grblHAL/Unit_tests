#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    ppi_command(LaserPPI_Rate, 254, STATE_IDLE);
    ppi_command(LaserPPI_PulseLength, 200, STATE_IDLE);
    ppi_command(LaserPPI_Enable, 1, STATE_IDLE);
    hal.stepper.wake_up();
    ppi_motor->update_rpm(ppi_motor, 500);
    ppi_move(951, 1000);
    CHECK(ppi_steps == 951 && ppi_pulses == 10 && ppi_width == 200 && ppi_updates == 1 &&
          ppi_wakes == 1);
    CHECK(ppi_locations[0] == 1);
    for (unsigned i = 2; i < ppi_pulses; i++)
    {
        unsigned delta = ppi_locations[i] - ppi_locations[i - 1];
        CHECK(delta >= 99 && delta <= 101);
    }
    return 0;
}
