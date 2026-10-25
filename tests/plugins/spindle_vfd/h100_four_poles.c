#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_poles = 4;
    vfd_min_frequency = 80;
    vfd_max_frequency = 6000;
    vfd_start();
    NEAR(vfd_motor->rpm_min, 240);
    NEAR(vfd_motor->rpm_max, 18000);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    vfd_expect(1, ModBus_WriteRegister, 0x201, 2000, true);
    return 0;
}
