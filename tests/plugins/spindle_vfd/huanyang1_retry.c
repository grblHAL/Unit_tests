#include "huanyang1_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_reject = 1;
    vfd_start();
    CHECK(vfd_requests == 2);
    vfd_clear_requests();
    vfd_ticks = 150;
    vfd_motor->get_state(vfd_motor);
    CHECK(vfd_requests == 0);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 1500);
    expect_frame(0, ModBus_ReadCoils, 8, 3, 0x90, 0, true);
    expect_frame(1, ModBus_ReadCoils, 8, 3, 0x0b, 0, true);
    expect_frame(2, ModBus_ReadCoils, 8, 3, 0x05, 0, true);
    expect_frame(3, ModBus_ReadHoldingRegisters, 6, 1, 1, 0, true);
    expect_frame(4, ModBus_WriteCoil, 7, 2, 0x09, 0xc4, true);
    CHECK(vfd_requests == 5 && vfd_alarms == 0);
    return 0;
}
