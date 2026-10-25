#include "huanyang1_host.h"
int main(void)
{
    vfd_rpm_50hz = 0;
    vfd_prepare(true);
    vfd_start();
    expect_discovery(0);
    vfd_clear_requests();
    vfd_motor->update_rpm(vfd_motor, 1500);
    expect_frame(0, ModBus_WriteCoil, 7, 2, 0x09, 0xc4, false);
    CHECK(vfd_requests == 1);
    return 0;
}
