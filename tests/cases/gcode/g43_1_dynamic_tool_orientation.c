#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G43.1X5Y5Z10";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 10.0f);
    char block2[] = "G49";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 0.0f);
    char block3[] = "G43.1X0Y0Z5";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.modal.tool_length_offset[Z_AXIS], 5.0f);

    return EXIT_SUCCESS;
}
