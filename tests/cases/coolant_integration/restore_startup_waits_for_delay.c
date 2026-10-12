#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    coolant_restore((coolant_state_t){.mist = true}, 100);
    CHECK(coolant_calls == 1 && actual_coolant.mist);
    CHECK(engine_ticks == 100);
    return EXIT_SUCCESS;
}
