#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(vfd_requests == 2);
    vfd_expect(0, ModBus_WriteCoil, 0x49, 0xff00, true);
    vfd_expect(1, ModBus_WriteRegister, 0x201, 1000, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On, .ccw = On}, 6000);
    CHECK(vfd_requests == 2);
    vfd_expect(0, ModBus_WriteCoil, 0x4a, 0xff00, true);
    vfd_expect(1, ModBus_WriteRegister, 0x201, 1000, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){0}, 0);
    vfd_expect(0, ModBus_WriteCoil, 0x4b, 0xff00, true);
    vfd_expect(1, ModBus_WriteRegister, 0x201, 100, true);
    return 0;
}
