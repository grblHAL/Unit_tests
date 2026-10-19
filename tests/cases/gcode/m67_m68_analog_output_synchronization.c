#include "support/incoming_gcode_host.h"
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("M67E0Q1") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("M68E0Q1") == Status_GcodeUnsupportedCommand);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
