#include "support/motion_mode_host.h"
int main(void)
{
    prepare_motion_modes();
    queue_motion_program("G0X1");
    char cancel[] = "G80";
    CHECK(gc_execute_block(cancel) == Status_OK);
    CHECK(gc_state.modal.motion == MotionMode_None);
    execute_motion_program();
    CHECK(rapid_steps == 80 && feed_steps == 0);
    CHECK(strncmp(rapid_report, "[GC:G0 ", 7) == 0);
    st_reset();
    CHECK(st_get_motion_mode() == MotionMode_None);
    return EXIT_SUCCESS;
}
