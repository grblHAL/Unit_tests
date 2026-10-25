#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_reject = 1;
    vfd_start();
    CHECK(vfd_requests == 1);
    vfd_ticks = 150;
    vfd_motor->get_state(vfd_motor);
    CHECK(vfd_requests == 1);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(vfd_requests == 5);
    vfd_expect(0, ModBus_ReadHoldingRegisters, 143, 1, true);
    vfd_expect(1, ModBus_ReadHoldingRegisters, 11, 1, true);
    vfd_expect(2, ModBus_ReadHoldingRegisters, 5, 1, true);
    vfd_expect(3, ModBus_WriteCoil, 0x49, 0xff00, true);
    vfd_expect(4, ModBus_WriteRegister, 0x201, 1000, true);
    return 0;
}
