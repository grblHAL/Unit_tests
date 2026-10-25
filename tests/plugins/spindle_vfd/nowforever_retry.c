#include "nowforever_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_reject = 1;
    vfd_start();
    CHECK(vfd_requests == 1);
    vfd_clear_requests();
    vfd_ticks = 150;
    vfd_motor->get_state(vfd_motor);
    CHECK(vfd_requests == 0);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    vfd_expect(0, ModBus_ReadHoldingRegisters, 7, 2, true);
    expect_write(1, 0x900, 1, true);
    expect_write(2, 0x901, 10002, true);
    CHECK(vfd_requests == 3 && vfd_alarms == 0);
    return 0;
}
