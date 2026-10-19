#include "support/incoming_gcode_host.h"
#include "check.h"
#include <string.h>

int main(void)
{
    prepare_incoming_parser();
    char block1[] = "G41D1";
    CHECK(gc_execute_block(block1) == Status_GcodeUnsupportedCommand);
    char block2[] = "G42D2";
    CHECK(gc_execute_block(block2) == Status_GcodeUnsupportedCommand);
    char block3[] = "G40";
    CHECK(gc_execute_block(block3) == Status_OK);

    return EXIT_SUCCESS;
}
