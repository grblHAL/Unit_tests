#include "huanyang1_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 1500);
    vfd_clear_requests();
    vfd_feedback = 2500;
    vfd_ticks = 150;
    CHECK(vfd_motor->get_state(vfd_motor).at_speed);
    expect_frame(0, ModBus_ReadInputRegisters, 8, 3, 1, 0, false);
    expect_frame(1, ModBus_ReadInputRegisters, 8, 3, 2, 0, false);
    NEAR(vfd_motor->get_data(SpindleData_AtSpeed)->rpm, 1500);
    vfd_ticks = 299;
    vfd_motor->get_state(vfd_motor);
    CHECK(vfd_requests == 2);
    vfd_feedback = 2000;
    vfd_ticks = 300;
    CHECK(!vfd_motor->get_state(vfd_motor).at_speed);
    NEAR(vfd_motor->get_data(SpindleData_AtSpeed)->rpm, 1200);
    CHECK(vfd_requests == 4);
    return 0;
}
