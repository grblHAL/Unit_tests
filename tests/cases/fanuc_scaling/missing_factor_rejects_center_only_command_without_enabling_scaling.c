#include "support/fanuc_scaling_host.h"
int main(void)
{
    engine_parser_prepare();
    CHECK(scaling_block("G0X5Y10Z15") == Status_OK);
    CHECK(scaling_block("G51X3Y4Z5") == Status_GcodeNoAxisWords);
    CHECK(!gc_state.modal.scaling_active);
    NEAR(gc_get_scaling()[0], 1); NEAR(gc_get_scaling()[1], 1); NEAR(gc_get_scaling()[2], 1);
    CHECK(scaling_block("G0X6Y12Z18") == Status_OK);
    NEAR(gc_state.position[0], 6); NEAR(gc_state.position[1], 12); NEAR(gc_state.position[2], 18);
    return EXIT_SUCCESS;
}
