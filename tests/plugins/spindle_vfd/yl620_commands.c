#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    CHECK(vfd_requests == 0 && vfd_previous_selected == 1);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(vfd_requests == 2);
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 0x12, true);
    vfd_expect(1, ModBus_WriteRegister, 0x2001, 1000, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On, .ccw = On}, 6000);
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 0x22, true);
    vfd_expect(1, ModBus_WriteRegister, 0x2001, 1000, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){0}, 0);
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 0x11, true);
    vfd_expect(1, ModBus_WriteRegister, 0x2001, 0, true);
    CHECK(vfd_requests == 2);
    return 0;
}
