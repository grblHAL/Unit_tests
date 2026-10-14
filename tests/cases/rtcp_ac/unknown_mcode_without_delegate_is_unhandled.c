#include "support/rtcp_host.h"

int main(void)
{
    prepare_rtcp();
    parser_block_t block = {.user_mcode = (user_mcode_t)900};
    CHECK(grbl.user_mcode.validate(&block) == Status_Unhandled);
    CHECK(!block.user_mcode_sync);
    grbl.user_mcode.execute(STATE_IDLE, &block);
    mpos_t steps = {.x = 80, .y = 160, .z = 240};
    coord_data_t actual;
    kinematics.transform_steps_to_cartesian(&actual, &steps);
    NEAR(actual.x, 1); NEAR(actual.y, 2); NEAR(actual.z, 3);
    return EXIT_SUCCESS;
}
