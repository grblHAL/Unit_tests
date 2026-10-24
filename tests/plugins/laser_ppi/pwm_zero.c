#include "ppi_host.h"
int main(void)
{
    ppi_prepare(true, true);
    ppi_command(LaserPPI_Enable, 1, STATE_IDLE);
    ppi_motor->update_pwm(ppi_motor, 500);
    unsigned before = ppi_pulses;
    CHECK(before == 1);
    ppi_motor->update_pwm(ppi_motor, 0);
    CHECK(ppi_updates == 2);
    CHECK(ppi_pulses == before);
    return 0;
}
