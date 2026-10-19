#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G61.1 - Exact stop mode (same as G61)
    char block1[] = "G61.1";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_ExactStop);

    // G64 - Continuous mode
    char block2[] = "G64";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_Continuous);

    // G61 - Exact stop mode
    char block3[] = "G61";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_ExactStop);

    // G61.1 again
    char block4[] = "G61.1";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(gc_state.modal.path_control == PathControl_ExactStop);

    return EXIT_SUCCESS;
}