#include "support/control_host.h"
#include "check.h"
static unsigned calls;
static coolant_state_t last;
static void set(coolant_state_t value) { calls++; last = value; }
static coolant_state_t get(void) { return last; }
int main(void)
{
    hal.coolant.get_state = get;
    hal.coolant.set_state = set; hal.coolant.get_state = get; sys.suspend = true;
    coolant_state_t mode = {.flood = 1}; coolant_restore(mode, 500);
    CHECK(calls == 1); CHECK(host_reports == 1); CHECK(host_delay_calls == 1);
    NEAR(host_delay_seconds, .5f); CHECK(host_delay_mode == DelayMode_SysSuspend);
    return EXIT_SUCCESS;
}
