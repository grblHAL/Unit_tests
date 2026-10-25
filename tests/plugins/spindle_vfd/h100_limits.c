#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_clear_requests();
    vfd_motor->update_rpm(vfd_motor, 300);
    vfd_expect(0, ModBus_WriteRegister, 0x201, 100, false);
    vfd_motor->update_rpm(vfd_motor, 30000);
    vfd_expect(1, ModBus_WriteRegister, 0x201, 4000, false);
    CHECK(vfd_requests == 2);
    return 0;
}
