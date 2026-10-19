#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G64 P0.01 - Continuous mode with 0.01mm tolerance
    char block1[] = "G64P0.01";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_Continuous);
    NEAR(gc_state.modal.path_tolerance, 0.01f);

    // G64 P0 - Continuous mode with zero tolerance (exact stop)
    char block2[] = "G64P0";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_Continuous);
    NEAR(gc_state.modal.path_tolerance, 0.0f);

    // G64 - Continuous mode default
    char block3[] = "G64";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_Continuous);

    return EXIT_SUCCESS;
}