#include "support/engine_host.h"
#include "check.h"
#include <string.h>
#include "ngc_params.h"
#include "check.h"

int main(void)
{
    engine_parser_prepare();
    settings.steppers.is_rotary.mask = (1u << 3) | (1u << 4) | (1u << 5);
    char block[] = "G20G1X1A4B5C6U1V1F100";
    CHECK(gc_execute_block(block) == Status_OK);
    NEAR(gc_state.position[X_AXIS], 25.4f);
    NEAR(gc_state.position[3], 4);
    NEAR(gc_state.position[4], 5);
    NEAR(gc_state.position[5], 6);
    NEAR(gc_state.position[6], 25.4f);
    NEAR(gc_state.position[7], 25.4f);
    return EXIT_SUCCESS;
}
