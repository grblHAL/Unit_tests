#include "support/explicit_probe_program_host.h"
int main(void)
{
    prepare_explicit_probe();
    CHECK(explicit_probe_block("G38.2X1F100P2") == Status_OK);
    check_explicit_contact(Probe_2, Probe_Default, 56);
    CHECK(explicit_selection_calls == 2);
    return EXIT_SUCCESS;
}
