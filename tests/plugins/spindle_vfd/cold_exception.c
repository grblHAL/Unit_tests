#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    sys.cold_start = true;
    vfd_exception = 1;
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(vfd_alarms == 0);
    vfd_run_tasks();
    CHECK(vfd_alarms == 1);
    return 0;
}
