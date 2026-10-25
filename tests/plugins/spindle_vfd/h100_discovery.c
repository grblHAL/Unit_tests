#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    CHECK(vfd_requests == 3 && vfd_previous_selected == 1 && vfd_silences == 1);
    vfd_expect(0, ModBus_ReadHoldingRegisters, 143, 1, true);
    vfd_expect(1, ModBus_ReadHoldingRegisters, 11, 1, true);
    vfd_expect(2, ModBus_ReadHoldingRegisters, 5, 1, true);
    CHECK(vfd_motor->cap.rpm_range_locked);
    NEAR(vfd_motor->rpm_min, 600);
    NEAR(vfd_motor->rpm_max, 24000);
    return 0;
}
