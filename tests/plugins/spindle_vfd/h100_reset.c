#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_clear_requests();
    vfd_min_frequency = 200;
    vfd_max_frequency = 3000;
    hal.driver_reset();
    CHECK(vfd_resets == 1 && vfd_requests == 0);
    vfd_run_tasks();
    CHECK(vfd_requests == 3);
    NEAR(vfd_motor->rpm_min, 1200);
    NEAR(vfd_motor->rpm_max, 18000);
    vfd_expect(0, ModBus_ReadHoldingRegisters, 143, 1, true);
    vfd_expect(1, ModBus_ReadHoldingRegisters, 11, 1, true);
    vfd_expect(2, ModBus_ReadHoldingRegisters, 5, 1, true);
    return 0;
}
