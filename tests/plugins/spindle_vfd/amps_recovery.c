#include "huanyang1_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 1500);
    vfd_feedback = 2500;
    for (unsigned i = 0; i < VFD_ASYNC_EXCEPTION_LEVEL + 1; i++)
    {
        vfd_clear_requests();
        vfd_exception = 2;
        vfd_ticks += 150;
        CHECK(vfd_motor->get_state(vfd_motor).at_speed);
        CHECK(vfd_requests == 2 && vfd_alarms == 0);
    }
    vfd_clear_requests();
    vfd_ticks += 150;
    CHECK(vfd_motor->get_state(vfd_motor).at_speed);
    CHECK(vfd_requests == 2 && vfd_alarms == 0);
    return 0;
}
