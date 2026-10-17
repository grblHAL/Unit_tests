#include "support/motion_program_host.h"
static unsigned comments;
static status_code_t capture_note(char *text)
{
    CHECK(strcmp(text, "Rough;finish") == 0);
    comments++;
    return Status_OK;
}
int main(void)
{
    prepare_motion_program();
    grbl.on_gcode_comment = capture_note;
    queue_motion_program("G1X1(Rough;finish)F100");
    CHECK(comments == 1);
    NEAR(gc_state.feed_rate, 100);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80 && physical_position[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
