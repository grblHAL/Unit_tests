#include "support/lathe_cycle_capture_host.h"
#include "check.h"

int main(void)
{
    prepare_lathe_capture(); CHECK(css_block("G71.3X10Z20Q7F100") == Status_GcodeUnsupportedCommand);
    CHECK(lathe_cycle_calls == 0); CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
