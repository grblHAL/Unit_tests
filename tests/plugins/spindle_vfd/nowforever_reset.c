#include "nowforever_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_clear_requests();
    vfd_min_frequency = 200;
    vfd_max_frequency = 30000;
    hal.driver_reset();
    CHECK(vfd_resets == 1 && vfd_requests == 0);
    vfd_run_tasks();
    vfd_expect(0, ModBus_ReadHoldingRegisters, 7, 2, true);
    NEAR(vfd_motor->rpm_min, 120);
    NEAR(vfd_motor->rpm_max, 18000);
    vfd_motor->update_rpm(vfd_motor, 24000);
    expect_write(1, 0x901, 30000, false);
    CHECK(vfd_requests == 2);
    return 0;
}
