#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // G41 D1 - Cutter compensation left with tool 1
    char block1[] = "G41D1";
    CHECK(gc_execute_block(block1) == Status_GcodeUnsupportedCommand); // Cutter comp not enabled

    // G42 D2 - Cutter compensation right with tool 2
    char block2[] = "G42D2";
    CHECK(gc_execute_block(block2) == Status_GcodeUnsupportedCommand);

    // G40 - Cancel
    char block3[] = "G40";
    CHECK(gc_execute_block(block3) == Status_OK);

    return EXIT_SUCCESS;
}