#include "support/pre_execute_host.h"

int main(void)
{
    prepare_pre_execute();
    pre_execute_result = Status_GcodeInvalidTarget;
    CHECK(pre_execute_block("G20G1X1F2") == Status_GcodeInvalidTarget);
    CHECK(pre_execute_calls == 1);
    NEAR(pre_execute_x, 25.4f);
    CHECK(!gc_state.modal.units_imperial);
    NEAR(gc_state.position[X_AXIS], 0);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
