#include "support/wco_motion_host.h"
int main(void)
{
    prepare_motion_program();
    settings.status_report.sync_on_wco_change = false;
    queue_motion_program("G1X1F100");
    wco_block("G92X0");
    queue_motion_program("G1X1");
    NEAR(gc_get_offset(X_AXIS, false), 1);
    run_two_offset_moves(0, 1);
    return EXIT_SUCCESS;
}
