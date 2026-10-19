#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G40";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(!gc_state.modal.canned_cycle_active);
    char block2[] = "G41D1";
    CHECK(gc_execute_block(block2) == Status_GcodeUnsupportedCommand);
    char block3[] = "G42D1";
    CHECK(gc_execute_block(block3) == Status_GcodeUnsupportedCommand);

    return EXIT_SUCCESS;
}
