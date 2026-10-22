#include "support/pre_execute_host.h"

int main(void)
{
    prepare_pre_execute();
    CHECK(pre_execute_block("G20G1X1F2") == Status_OK);
    CHECK(pre_execute_calls == 1 && pre_execute_commands.G1);
    CHECK(!pre_execute_prior_inches && pre_execute_new_inches);
    NEAR(pre_execute_x, 25.4f);
    NEAR(pre_execute_feed, 50.8f);
    CHECK(gc_state.modal.units_imperial);
    NEAR(gc_state.position[X_AXIS], 25.4f);
    CHECK(plan_get_recent_block()->steps.value[X_AXIS] == 2032);
    return EXIT_SUCCESS;
}
