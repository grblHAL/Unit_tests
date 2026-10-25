#include "vfd_host.h"
int main(void)
{
    vfd_prepare(true);
    vfd_reject = 2;
    vfd_start();
#if TEST_H100
    CHECK(vfd_requests == 2);
#else
    CHECK(vfd_requests == 3);
#endif
    CHECK(!vfd_motor->cap.rpm_range_locked);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 1500);
    CHECK(vfd_requests == 5 && vfd_motor->cap.rpm_range_locked);
    CHECK(vfd_motor->get_data(SpindleData_AtSpeed)->rpm_programmed == 1500);
    CHECK(vfd_alarms == 0);
    return 0;
}
