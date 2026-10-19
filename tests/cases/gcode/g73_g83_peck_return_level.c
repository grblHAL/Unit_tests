#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G73X10Y10Z-20R5Q3F100";
    CHECK(gc_execute_block(block1) == Status_OK);
    char block2[] = "G83X20Y20Z-30R5Q5F100";
    CHECK(gc_execute_block(block2) == Status_OK);
    char block3[] = "G98";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.retract_mode == CCRetractMode_Previous);
    char block4[] = "G99";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(gc_state.modal.retract_mode == CCRetractMode_RPos);
    char block5[] = "G80";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}
