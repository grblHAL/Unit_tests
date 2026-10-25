#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_start();
    vfd_clear_requests();
    vfd_reject = 1;
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(vfd_requests == 1);
    CHECK(vfd_motor->get_data(SpindleData_AtSpeed)->rpm_programmed == -1);
    return 0;
}
