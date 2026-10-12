#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    settings.coolant.on_delay = 100;
    actual_coolant.flood = true;
    coolant_set_state((coolant_state_t){0});
    CHECK(coolant_calls == 1 && actual_coolant.value == 0);
    CHECK(engine_ticks == 0);
    return EXIT_SUCCESS;
}
