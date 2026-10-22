#include "support/pre_execute_host.h"

int main(void)
{
    prepare_pre_execute();
    CHECK(pre_execute_block("G1X1F100") == Status_OK);
    CHECK(pre_execute_block("X2") == Status_OK);
    CHECK(pre_execute_calls == 2 && pre_execute_commands.G1);
    NEAR(pre_execute_x, 2);
    NEAR(gc_state.position[X_AXIS], 2);
    CHECK(plan_get_recent_block()->steps.value[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
