#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    CHECK(vfd_flushes == 1 && vfd_silences == 1 && vfd_previous_selected == 1);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(vfd_requests == 2);
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 0x12, true);
#if TEST_MODVFD
    vfd_expect(1, ModBus_WriteRegister, 0x2001, 5000, true);
#else
    vfd_expect(1, ModBus_WriteRegister, 0x2001, 10000, true);
#endif
    CHECK(vfd_motor->get_data(SpindleData_AtSpeed)->rpm_programmed == 6000);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On, .ccw = On}, 6000);
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 0x22, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){0}, 0);
#if TEST_MODVFD
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 1, true);
#else
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 0x11, true);
#endif
    CHECK(vfd_requests == 2 && vfd_messages[1].adu[4] == 0 && vfd_messages[1].adu[5] == 0);
    return 0;
}
