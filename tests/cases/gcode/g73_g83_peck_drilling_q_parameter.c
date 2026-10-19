#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G73 X10 Y10 Z-20 R5 Q3 F100 - High speed peck, 3mm peck increment
    char block1[] = "G73X10Y10Z-20R5Q3F100";
    CHECK(gc_execute_block(block1) == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_G73);

    // G83 X20 Y20 Z-30 R5 Q5 F100 - Peck drilling, 5mm peck increment
    char block2[] = "G83X20Y20Z-30R5Q5F100";
    CHECK(gc_execute_block(block2) == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_G83);

    // G80 - Cancel
    char block3[] = "G80";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_Cancel);

    // G73 without Q - Should fail
    char block4[] = "G73X10Y10Z-20R5F100";
    CHECK(gc_execute_block(block4) == Status_GcodeValueWordMissing);

    // G83 without Q - Should fail
    char block5[] = "G83X10Y10Z-20R5F100";
    CHECK(gc_execute_block(block5) == Status_GcodeValueWordMissing);

    return EXIT_SUCCESS;
}