#include <string.h>
#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare(); char block[] = "G20G21";
    CHECK(gc_execute_block(block) == Status_GcodeModalGroupViolation); CHECK(!gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
