#include "support/explicit_probe_program_host.h"
int main(void)
{
    prepare_explicit_probe();
    CHECK(hal.probe.select(Probe_2));
    explicit_selection_calls = 0;
    CHECK(explicit_probe_block("G38.2X1F100P0") == Status_OK);
    check_explicit_contact(Probe_Default, Probe_2, 40);
    CHECK(explicit_selection_calls == 2);
    return EXIT_SUCCESS;
}
