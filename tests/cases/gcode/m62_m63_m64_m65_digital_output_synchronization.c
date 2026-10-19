#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("M62P0") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("M63P0") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("M64P0") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("M65P0") == Status_GcodeUnsupportedCommand);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
