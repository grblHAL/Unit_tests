#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    coolant_set_state((coolant_state_t){.flood = true});
    CHECK(coolant_calls == 1 && actual_coolant.flood && !actual_coolant.mist);
    CHECK(hal.stream.report.flags.value & Report_Coolant);
    return EXIT_SUCCESS;
}
