#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    coolant_set_state((coolant_state_t){.mist = true});
    CHECK(coolant_calls == 1 && actual_coolant.mist && !actual_coolant.flood);
    return EXIT_SUCCESS;
}
