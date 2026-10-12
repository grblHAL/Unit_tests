#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    CHECK(coolant_set_state_synced((coolant_state_t){.flood = true}));
    CHECK(coolant_calls == 1 && actual_coolant.flood);
    return EXIT_SUCCESS;
}
