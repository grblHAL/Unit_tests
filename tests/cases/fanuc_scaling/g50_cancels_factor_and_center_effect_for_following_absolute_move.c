#include "support/fanuc_scaling_host.h"
int main(void)
{
    engine_parser_prepare();
    CHECK(scaling_block("G51X5Y10Z15P2") == Status_OK);
    CHECK(scaling_block("G0X6Y12Z18") == Status_OK);
    NEAR(gc_state.position[0], 7);
    CHECK(scaling_block("G50") == Status_OK);
    CHECK(!gc_state.modal.scaling_active);
    CHECK(scaling_block("G0X6Y12Z18") == Status_OK);
    NEAR(gc_state.position[0], 6); NEAR(gc_state.position[1], 12); NEAR(gc_state.position[2], 18);
    return EXIT_SUCCESS;
}
