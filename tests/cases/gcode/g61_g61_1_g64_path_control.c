#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G61 - Exact stop mode
    char block1[] = "G61";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_ExactStop);

    // G61.1 - Exact stop mode (same as G61)
    char block2[] = "G61.1";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_ExactStop);

    // G64 - Continuous mode (default)
    char block3[] = "G64";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_Continuous);

    // G64 P0.01 - Continuous with tolerance
    char block4[] = "G64P0.01";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_Continuous);
    NEAR(gc_state.modal.path_tolerance, 0.01f);

    return EXIT_SUCCESS;
}