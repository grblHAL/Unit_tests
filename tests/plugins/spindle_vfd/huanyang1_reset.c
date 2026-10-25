#include "huanyang1_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_clear_requests();
    vfd_rpm_50hz = 1500;
    hal.driver_reset();
    CHECK(vfd_resets == 1 && vfd_requests == 0);
    vfd_run_tasks();
    expect_discovery(0);
    NEAR(vfd_motor->rpm_min, 30);
    NEAR(vfd_motor->rpm_max, 1200);
    vfd_motor->update_rpm(vfd_motor, 750);
    expect_frame(4, ModBus_WriteCoil, 7, 2, 0x09, 0xc4, false);
    CHECK(vfd_requests == 5);
    return 0;
}
