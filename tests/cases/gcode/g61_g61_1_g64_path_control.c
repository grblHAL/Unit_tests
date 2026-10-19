#include "support/incoming_gcode_host.h"
/* Path blending is explicitly disabled by core/config.h. */
int main(void)
{
    prepare_incoming_parser();
    CHECK(incoming_block("G61") == Status_OK);
    CHECK(incoming_block("G61.1") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("G64") == Status_GcodeUnsupportedCommand);
    CHECK(incoming_block("G64P0.01") == Status_GcodeUnsupportedCommand);
    CHECK(gc_state.modal.motion == MotionMode_Seek);
    CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
