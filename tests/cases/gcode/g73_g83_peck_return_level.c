#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G73 X10 Y10 Z-20 R5 Q3 F100 - R is return level
    char block1[] = "G73X10Y10Z-20R5Q3F100";
    CHECK(gc_execute_block(block1) == Status_OK);

    // G83 X20 Y20 Z-30 R5 Q5 F100 - R is return level
    char block2[] = "G83X20Y20Z-30R5Q5F100";
    CHECK(gc_execute_block(block2) == Status_OK);

    // G98 - Return to initial level after canned cycle
    char block3[] = "G98";
    CHECK(gc_execute_block(block3) == Status_OK);
    CHECK(gc_state.modal.canned_return == CannedReturn_Initial);

    // G99 - Return to R level after canned cycle
    char block4[] = "G99";
    CHECK(gc_execute_block(block4) == Status_OK);
    CHECK(gc_state.modal.canned_return == CannedReturn_RPlane);

    // G80 - Cancel
    char block5[] = "G80";
    CHECK(gc_execute_block(block5) == Status_OK);

    return EXIT_SUCCESS;
}