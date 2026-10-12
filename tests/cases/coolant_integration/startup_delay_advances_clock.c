#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    settings.coolant.on_delay = 100;
    coolant_set_state((coolant_state_t){.flood = true});
    CHECK(coolant_calls == 1 && actual_coolant.flood);
    CHECK(engine_ticks == 100);
    return EXIT_SUCCESS;
}
