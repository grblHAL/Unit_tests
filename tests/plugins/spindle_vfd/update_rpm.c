#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_motor->update_rpm(vfd_motor, 12000);
    CHECK(vfd_requests == 1);
#if TEST_MODVFD
    vfd_expect(0, ModBus_WriteRegister, 0x2001, 10000, false);
#else
    vfd_expect(0, ModBus_WriteRegister, 0x2001, 20000, false);
#endif
    CHECK(vfd_motor->get_data(SpindleData_AtSpeed)->rpm_programmed == 12000);
    return 0;
}
