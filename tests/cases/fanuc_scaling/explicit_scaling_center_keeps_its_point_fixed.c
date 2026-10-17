#include "support/fanuc_scaling_host.h"
int main(void)
{
    engine_parser_prepare();
    CHECK(scaling_block("G51X5Y10Z15P2") == Status_OK);
    CHECK(scaling_block("G0X5Y10Z15") == Status_OK);
    NEAR(gc_state.position[0], 5); NEAR(gc_state.position[1], 10); NEAR(gc_state.position[2], 15);
    CHECK(scaling_block("G0X6Y12Z18") == Status_OK);
    NEAR(gc_state.position[0], 7); NEAR(gc_state.position[1], 14); NEAR(gc_state.position[2], 21);
    return EXIT_SUCCESS;
}
