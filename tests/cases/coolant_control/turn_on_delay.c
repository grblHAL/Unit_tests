#include "support/control_host.h"
#include "check.h"
static unsigned calls;
static coolant_state_t last;
static void set(coolant_state_t value) { calls++; last = value; }
static coolant_state_t get(void) { return last; }
int main(void)
{
    hal.coolant.get_state = get;
    hal.coolant.set_state = set; settings.coolant.on_delay = 250;
    coolant_state_t mode = {.flood = 1}; coolant_set_state(mode);
    CHECK(calls == 1); CHECK(host_delay_calls == 1); NEAR(host_delay_seconds, .25f); CHECK(host_delay_mode == DelayMode_Dwell);
    mode.value = 0; coolant_set_state(mode); CHECK(host_delay_calls == 1);
    return EXIT_SUCCESS;
}
