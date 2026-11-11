#include "enable_host.h"

int main(void)
{
    enable_prepare_ports(false);
    vfd_prepare(true);
    vfd_start();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(enable_levels[3]);
    vfd_clear_requests();
    hal.driver_reset();
    CHECK(!enable_levels[3] && vfd_resets == 1 && !vfd_requests);
    /* A real MODVFD exception callback must quench the output during the send. */
    vfd_exception = 1;
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(vfd_alarms == 1 && !enable_levels[3]);
    vfd_clear_requests();
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(enable_levels[3]);
    hal.driver_reset();
    CHECK(!enable_levels[3] && vfd_resets == 2);
    enable_expect_claim(true);
    return 0;
}
