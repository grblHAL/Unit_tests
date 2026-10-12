#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    char block[] = "G20G1F-1X2";
    CHECK(gc_execute_block(block) == Status_NegativeValue);
    CHECK(!gc_state.modal.units_imperial);
    CHECK(gc_state.position[X_AXIS] == 0);
    return EXIT_SUCCESS;
}
