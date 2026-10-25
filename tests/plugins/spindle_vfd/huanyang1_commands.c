#include "huanyang1_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    expect_discovery(0);
    CHECK(vfd_requests == 4 && vfd_silences == 2);
    CHECK(vfd_motor->cap.rpm_range_locked);
    NEAR(vfd_motor->rpm_min, 60);
    NEAR(vfd_motor->rpm_max, 2400);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 1500);
    expect_frame(0, ModBus_ReadHoldingRegisters, 6, 1, 1, 0, true);
    expect_frame(1, ModBus_WriteCoil, 7, 2, 0x09, 0xc4, true);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On, .ccw = On}, 1500);
    expect_frame(0, ModBus_ReadHoldingRegisters, 6, 1, 0x11, 0, true);
    expect_frame(1, ModBus_WriteCoil, 7, 2, 0x09, 0xc4, true);
    vfd_clear_requests();
    vfd_motor->update_rpm(vfd_motor, 1800);
    expect_frame(0, ModBus_WriteCoil, 7, 2, 0x0b, 0xb8, false);
    vfd_motor->update_rpm(vfd_motor, 1800);
    CHECK(vfd_requests == 1);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){0}, 0);
    expect_frame(0, ModBus_ReadHoldingRegisters, 6, 1, 8, 0, true);
    expect_frame(1, ModBus_WriteCoil, 7, 2, 0, 0, true);
    CHECK(vfd_requests == 2);
    return 0;
}
