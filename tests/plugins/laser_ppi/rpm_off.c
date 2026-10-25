#include "ppi_host.h"
int main(void)
{
    ppi_prepare(false, true);
    ppi_command(LaserPPI_Enable, 1, STATE_IDLE);
    ppi_motor->update_rpm(ppi_motor, 0);
    ppi_move(20, 1000);
    CHECK(!ppi_pulses && ppi_steps == 20);
    ppi_motor->update_rpm(ppi_motor, 500);
    ppi_move(1, 1000);
    CHECK(ppi_pulses == 1);
    ppi_motor->update_rpm(ppi_motor, 0);
    ppi_move(20, 1000);
    CHECK(ppi_pulses == 1 && ppi_updates == 3);
    return 0;
}
