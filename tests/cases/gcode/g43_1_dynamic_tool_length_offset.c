#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G43.1 Z10 - Dynamic tool length offset
    char block1[] = "G43.1Z10";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset, 10.0f);

    // G49 - Cancel tool length offset
    char block2[] = "G49";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset, 0.0f);

    // G43.1 with X/Y/Z axes
    char block3[] = "G43.1X5Y5Z10";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset, 10.0f); // Z axis is length

    // G43.1 without axis - should fail
    char block4[] = "G43.1";
    CHECK(gc_execute_block(block4) == Status_GcodeNoAxisWords);

    return EXIT_SUCCESS;
}