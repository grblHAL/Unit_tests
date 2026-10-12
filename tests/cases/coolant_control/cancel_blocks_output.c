#include "support/control_host.h"
#include "check.h"
static unsigned calls;
static coolant_state_t last;
static void set(coolant_state_t value) { calls++; last = value; }
static coolant_state_t get(void) { return last; }
int main(void)
{
    hal.coolant.get_state = get;
    hal.coolant.set_state = set; sys.cancel = true;
    coolant_state_t mode = {.mist = 1}; coolant_set_state(mode);
    CHECK(calls == 0); CHECK(host_reports == 0);
    return EXIT_SUCCESS;
}
