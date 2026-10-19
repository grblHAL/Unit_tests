#include "support/engine_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    engine_parser_prepare();

    // M98 P100 - Call subprogram 100
    // This requires a file stream or macro handler
    char block1[] = "M98P100";
    CHECK(gc_execute_block(block1) == Status_GcodeUnsupportedCommand); // No file stream

    // M99 - Return from subprogram
    char block2[] = "M99";
    CHECK(gc_execute_block(block2) == Status_GcodeUnsupportedCommand); // No macro return handler

    return EXIT_SUCCESS;
}