#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_clear_requests();
    vfd_max_rpm = 18000;
    hal.driver_reset();
    CHECK(vfd_resets == 1 && vfd_requests == 0);
    vfd_run_tasks();
    vfd_expect(0, ModBus_ReadHoldingRegisters, 0xb005, 2, true);
    vfd_motor->update_rpm(vfd_motor, 9000);
    vfd_expect(1, ModBus_WriteRegister, 0x1000, 5000, false);
    CHECK(vfd_requests == 2);
    return 0;
}
