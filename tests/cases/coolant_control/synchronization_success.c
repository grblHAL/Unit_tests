#include "support/control_host.h"
#include "check.h"
static unsigned calls;
static coolant_state_t last;
static void set(coolant_state_t value) { calls++; last = value; }
static coolant_state_t get(void) { return last; }
int main(void)
{
    hal.coolant.get_state = get;
    hal.coolant.set_state = set;
    coolant_state_t mode = {.mist = 1}; CHECK(coolant_set_state_synced(mode));
    CHECK(calls == 1); CHECK(host_sync_calls == 1); CHECK(last.mist);
    return EXIT_SUCCESS;
}
