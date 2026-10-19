#include "support/wco_status_motion_host.h"
int main(void)
{
    prepare_wco_status_motion();
    queue_motion_program("G1X1F100");
    wco_block("G92X0");
    queue_motion_program("G1X1");
    expected_work_positions[0] = expected_work_positions[1] = "|WPos:0.500,0.000,0.000";
    expected_work_offsets[0] = "|WCO:0.000,0.000,0.000";
    expected_work_offsets[1] = "|WCO:1.000,0.000,0.000";
    run_two_offset_moves(0, 1);
    CHECK(wco_status_samples == 2);
    return EXIT_SUCCESS;
}
