#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    actual_coolant.mist = true;
    coolant_restore((coolant_state_t){.flood = true}, 0);
    CHECK(coolant_calls == 1 && actual_coolant.flood && !actual_coolant.mist);
    CHECK(hal.stream.report.flags.value & Report_Coolant);
    return EXIT_SUCCESS;
}
