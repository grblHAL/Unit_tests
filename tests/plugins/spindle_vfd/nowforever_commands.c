#include "nowforever_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_expect(0, ModBus_ReadHoldingRegisters, 7, 2, true);
    CHECK(vfd_motor->cap.rpm_range_locked);
    NEAR(vfd_motor->rpm_min, 60);
    NEAR(vfd_motor->rpm_max, 24000);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    expect_write(0, 0x900, 1, true);
    expect_write(1, 0x901, 10002, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On, .ccw = On}, 6000);
    expect_write(0, 0x900, 3, true);
    expect_write(1, 0x901, 10002, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.ccw = On}, 0);
    expect_write(0, 0x900, 0, true);
    expect_write(1, 0x901, 100, true);
    CHECK(vfd_requests == 2);
    return 0;
}
