#include "support/motion_mode_host.h"
int main(void)
{
    prepare_motion_modes();
    queue_motion_program("G0X1");
    queue_motion_program("G1X2F100");
    execute_motion_program();
    CHECK(strncmp(rapid_report,"[GC:G0 ",7) == 0);
    CHECK(strncmp(feed_report,"[GC:G1 ",7) == 0);
    CHECK(sys.position[X_AXIS] == 160);
    return EXIT_SUCCESS;
}
