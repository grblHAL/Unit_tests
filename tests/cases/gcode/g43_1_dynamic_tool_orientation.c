#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G43.1 X5 Y5 Z10 - Dynamic tool length with orientation
    char block1[] = "G43.1X5Y5Z10";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset, 10.0f);

    // G49 - Cancel
    char block2[] = "G49";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset, 0.0f);

    // G43.1 X0 Y0 Z5 - Dynamic tool length
    char block3[] = "G43.1X0Y0Z5";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset, 5.0f);

    return EXIT_SUCCESS;
}