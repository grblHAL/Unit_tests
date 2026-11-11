#include "enable_host.h"

int main(void)
{
    enable_prepare_ports(true);
    vfd_prepare(true);
    vfd_run_tasks();
    CHECK(vfd_warnings == 1);
    vfd_start();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){0}, 0);
    CHECK(vfd_requests == 4 && !vfd_alarms && !enable_writes[3]);
    enable_expect_claim(false);
    return 0;
}
