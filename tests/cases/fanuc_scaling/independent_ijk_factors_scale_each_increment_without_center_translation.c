#include "support/fanuc_scaling_host.h"
int main(void)
{
    engine_parser_prepare();
    CHECK(scaling_block("G0X5Y10Z15") == Status_OK);
    CHECK(scaling_block("G51I2J3K4") == Status_OK);
    CHECK(scaling_block("G91G0X1Y2Z3") == Status_OK);
    NEAR(gc_state.position[0], 7); NEAR(gc_state.position[1], 16); NEAR(gc_state.position[2], 27);
    return EXIT_SUCCESS;
}
