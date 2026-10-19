#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G73X10Y10Z-20R5Q3F100";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_DrillChipBreak);
    char block2[] = "G83X20Y20Z-30R5Q5F100";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_CannedCycle83);
    char block3[] = "G80";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_None);
    char block4[] = "G73X10Y10Z-20R5F100";
    CHECK(gc_execute_block(block4) == Status_GcodeValueWordMissing);
    char block5[] = "G83X10Y10Z-20R5F100";
    CHECK(gc_execute_block(block5) == Status_GcodeValueWordMissing);

    return EXIT_SUCCESS;
}
