#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    state_set(STATE_CHECK_MODE);
    CHECK(coolant_set_state_synced((coolant_state_t){.flood = true}));
    CHECK(coolant_calls == 0 && actual_coolant.value == 0);
    return EXIT_SUCCESS;
}
