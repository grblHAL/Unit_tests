#include "support/boot_host.h"
#include "check.h"

int main(void)
{
    boot_program = "G999\nG20\n";
    CHECK(grbl_enter() == 0);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(gc_state.last_error == Status_GcodeUnsupportedCommand);
    return EXIT_SUCCESS;
}
