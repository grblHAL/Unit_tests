#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    for (unsigned i = 1; i <= VFD_ASYNC_EXCEPTION_LEVEL; i++)
    {
        vfd_clear_requests();
        vfd_exception = 1;
        vfd_ticks += 150;
        vfd_motor->get_state(vfd_motor);
        CHECK(vfd_alarms == (i == VFD_ASYNC_EXCEPTION_LEVEL));
    }
    return 0;
}
