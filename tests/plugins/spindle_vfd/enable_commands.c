#include "enable_host.h"

static bool expected_level;
static unsigned observed_requests;
static void observe(const modbus_message_t *message, bool blocking)
{
    CHECK(message && blocking);
    CHECK(enable_levels[3] == expected_level);
    observed_requests++;
}
int main(void)
{
    enable_prepare_ports(false);
    vfd_prepare(true);
    enable_expect_claim(true);
    CHECK(enable_writes[3] == 1 && !enable_levels[3]);
    vfd_start();
    vfd_request_observer = observe;
    expected_level = true;
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 6000);
    CHECK(enable_levels[3] && observed_requests == 2);
    vfd_expect(0, ModBus_WriteRegister, 0x2000, 0x12, true);
    vfd_motor->set_state(vfd_motor, (spindle_state_t){.on = On}, 0);
    CHECK(enable_levels[3] && observed_requests == 4);
    vfd_expect(2, ModBus_WriteRegister, 0x2000, 1, true);
    expected_level = false;
    vfd_motor->set_state(vfd_motor, (spindle_state_t){0}, 0);
    CHECK(!enable_levels[3] && observed_requests == 6 && !vfd_alarms);
    enable_expect_claim(true);
    return 0;
}
