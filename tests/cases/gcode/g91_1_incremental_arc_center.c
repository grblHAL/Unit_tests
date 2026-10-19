#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G90G91.1";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.distance_incremental == false);
    char block2[] = "G2X10Y10I5J5F100";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G90G90.1";
    CHECK(gc_execute_block(block3) == Status_GcodeUnsupportedCommand);

    return EXIT_SUCCESS;
}
