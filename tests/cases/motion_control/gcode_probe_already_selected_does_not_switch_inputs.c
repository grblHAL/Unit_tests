#include "support/explicit_probe_program_host.h"
int main(void)
{
    prepare_explicit_probe();
    CHECK(hal.probe.select(Probe_Toolsetter));
    explicit_selection_calls = 0;
    CHECK(explicit_probe_block("G38.2X1F100P1") == Status_OK);
    check_explicit_contact(Probe_Toolsetter, Probe_Toolsetter, 64);
    CHECK(explicit_selection_calls == 0);
    return EXIT_SUCCESS;
}
