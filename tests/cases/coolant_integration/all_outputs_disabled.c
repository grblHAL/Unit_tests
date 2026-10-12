#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    actual_coolant.flood = actual_coolant.mist = true;
    coolant_set_state((coolant_state_t){0});
    CHECK(coolant_calls == 1 && actual_coolant.value == 0);
    return EXIT_SUCCESS;
}
