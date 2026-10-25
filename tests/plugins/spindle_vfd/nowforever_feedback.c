#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    vfd_clear_requests();
    vfd_feedback = 10000;
    vfd_ticks = 150;
    CHECK(vfd_motor->get_state(vfd_motor).at_speed);
    vfd_expect(0, ModBus_ReadHoldingRegisters, 0x502, 1, false);
    spindle_data_t *data = vfd_motor->get_data(SpindleData_AtSpeed);
    CHECK(fabsf(data->rpm - 6000) < 0.01f && fabsf(data->rpm_high_limit - 6300) < 0.01f);
    vfd_ticks = 299;
    vfd_motor->get_state(vfd_motor);
    CHECK(vfd_requests == 1);
    vfd_feedback = 8000;
    vfd_ticks = 300;
    CHECK(!vfd_motor->get_state(vfd_motor).at_speed);
    CHECK(fabsf(data->rpm - 4800) < 0.01f && vfd_requests == 2);
    return 0;
}
