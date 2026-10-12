#include "support/coolant_host.h"
#include "check.h"

int main(void)
{
    prepare_coolant();
    sys.abort = true;
    coolant_set_state((coolant_state_t){.flood = true});
    CHECK(coolant_calls == 0 && actual_coolant.value == 0);
    return EXIT_SUCCESS;
}
