#include "support/wco_motion_host.h"
int main(void)
{
    prepare_motion_program();
    settings.status_report.sync_on_wco_change = false;
    wco_block("G92X-1");
    queue_motion_program("G1X0F100");
    wco_block("G92.2");
    queue_motion_program("G1X2");
    NEAR(gc_get_offset(X_AXIS, false), 0);
    run_two_offset_moves(1, 0);
    return EXIT_SUCCESS;
}
