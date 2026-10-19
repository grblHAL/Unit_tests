#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G54G92X10Y20";
    CHECK(gc_execute_block(block1) == Status_OK);
    NEAR(gc_state.g92_offset.coord.values[0], -10.0f);
    NEAR(gc_state.g92_offset.coord.values[1], -20.0f);
    char block2[] = "G55G92X5Y5";
    CHECK(gc_execute_block(block2) == Status_OK);
    NEAR(gc_state.g92_offset.coord.values[0], -5.0f);
    NEAR(gc_state.g92_offset.coord.values[1], -5.0f);
    char block3[] = "G92.1";
    CHECK(gc_execute_block(block3) == Status_OK);
    NEAR(gc_state.g92_offset.coord.values[0], 0.0f);
    NEAR(gc_state.g92_offset.coord.values[1], 0.0f);

    return EXIT_SUCCESS;
}
