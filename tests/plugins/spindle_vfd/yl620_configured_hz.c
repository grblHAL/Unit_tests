#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_word(Setting_VFD_RPM_Hz, 120);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    vfd_expect(1, ModBus_WriteRegister, 0x2001, 500, true);
    vfd_clear_requests();
    vfd_feedback = 500;
    vfd_ticks = 150;
    CHECK(vfd_motor->get_state(vfd_motor).at_speed);
    CHECK(fabsf(vfd_motor->get_data(SpindleData_AtSpeed)->rpm - 6000) < 0.01f);
    return 0;
}
