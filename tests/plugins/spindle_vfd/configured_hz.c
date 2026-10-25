#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_word(Setting_VFD_RPM_Hz, 120);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    vfd_expect(1, ModBus_WriteRegister, 0x2001, 5000, true);
    vfd_feedback = 5000;
    vfd_ticks = 150;
    CHECK(vfd_motor->get_state(vfd_motor).at_speed);
    return 0;
}
