#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G51 X0 Y0 P2 - Scale by 2
    char block1[] = "G51X0Y0P2";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G53 G0 X10 Y10 - Machine coordinate move (ignores scaling)
    char block2[] = "G53G0X10Y10";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.position[0], 10.0f);
    NEAR(gc_state.position[1], 10.0f);

    // G0 X10 Y10 - Program coordinate move (with scaling)
    char block3[] = "G0X10Y10";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.position[0], 30.0f); // 10 + 10*2
    NEAR(gc_state.position[1], 30.0f);

    // G50 - Cancel scaling
    char block4[] = "G50";
    CHECK(gc_execute_block(block4) == Status_OK);

    return EXIT_SUCCESS;
}