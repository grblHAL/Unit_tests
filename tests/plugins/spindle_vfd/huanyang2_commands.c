#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    CHECK(vfd_requests == 1);
    vfd_expect(0, ModBus_ReadHoldingRegisters, 0xb005, 2, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 1, true);
    vfd_expect(1, ModBus_WriteRegister, 0x1000, 2500, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On, .ccw = On}, 6000);
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 2, true);
    vfd_expect(1, ModBus_WriteRegister, 0x1000, 2500, true);
    vfd_clear_requests();
    vfd_motor->update_rpm(vfd_motor, 12000);
    vfd_expect(0, ModBus_WriteRegister, 0x1000, 5000, false);
    vfd_motor->update_rpm(vfd_motor, 12000);
    CHECK(vfd_requests == 1);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){0}, 0);
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 6, true);
    vfd_expect(1, ModBus_WriteRegister, 0x1000, 0, true);
    CHECK(vfd_requests == 2);
    return 0;
}
