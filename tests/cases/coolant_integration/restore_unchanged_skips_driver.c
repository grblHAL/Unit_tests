#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    actual_coolant.flood = true;
    coolant_restore((coolant_state_t){.flood = true}, 100);
    CHECK(coolant_calls == 0 && engine_ticks == 0);
    return EXIT_SUCCESS;
}
