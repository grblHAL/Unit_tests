#include "support/spindle_multi_override_host.h"
int main(void)
{
    prepare_independent_spindle_overrides();
    CHECK(spindle_program_block("M51P0$0") == Status_OK);
    check_independent_spindle_override_outputs(3000, 8400);
    CHECK(spindle_get(0)->param->state.override_disable && !spindle_get(1)->param->state.override_disable);
    CHECK(spindle_program_block("M51P1$0") == Status_OK);
    check_independent_spindle_override_outputs(3300, 8400);
    CHECK(!spindle_get(0)->param->state.override_disable && !spindle_get(1)->param->state.override_disable);
    return EXIT_SUCCESS;
}
