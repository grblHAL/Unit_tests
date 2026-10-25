#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_reject = 1;
    vfd_start();
    CHECK(vfd_requests == 1);
    vfd_clear_requests();
    vfd_ticks = 150;
    vfd_motor->get_state(vfd_motor);
    CHECK(vfd_requests == 0);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    vfd_expect(0, ModBus_ReadHoldingRegisters, 0xb005, 2, true);
    vfd_expect(1, ModBus_WriteRegister, 0x2000, 1, true);
    vfd_expect(2, ModBus_WriteRegister, 0x1000, 2500, true);
    CHECK(vfd_requests == 3 && vfd_alarms == 0);
    return 0;
}
