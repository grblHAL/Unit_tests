#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_word(Setting_VFD_10, 0x1000);
    vfd_word(Setting_VFD_11, 0x1001);
    vfd_word(Setting_VFD_12, 0x1002);
    vfd_word(Setting_VFD_13, 7);
    vfd_word(Setting_VFD_14, 8);
    vfd_word(Setting_VFD_15, 9);
    vfd_float(Setting_VFD_16, 2);
    vfd_float(Setting_VFD_17, 3);
    vfd_float(Setting_VFD_18, 3);
    vfd_float(Setting_VFD_19, 2);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On, .ccw = On}, 6000);
    vfd_expect(0, ModBus_WriteRegister, 0x1000, 8, true);
    vfd_expect(1, ModBus_WriteRegister, 0x1001, 4000, true);
    vfd_clear_requests();
    vfd_feedback = 4000;
    vfd_ticks = 150;
    CHECK(vfd_motor->get_state(vfd_motor).at_speed);
    vfd_expect(0, ModBus_ReadHoldingRegisters, 0x1002, 1, false);
    return 0;
}
