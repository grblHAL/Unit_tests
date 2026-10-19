#include "support/wco_status_motion_host.h"
int main(void)
{
    prepare_wco_status_motion();
    wco_block("G92X-1");
    queue_motion_program("G1X0F100");
    wco_block("G92.2");
    queue_motion_program("G1X2");
    expected_work_positions[0] = "|WPos:-0.500,0.000,0.000";
    expected_work_positions[1] = "|WPos:1.500,0.000,0.000";
    expected_work_offsets[0] = "|WCO:1.000,0.000,0.000";
    expected_work_offsets[1] = "|WCO:0.000,0.000,0.000";
    run_two_offset_moves(1, 0);
    CHECK(wco_status_samples == 2);
    return EXIT_SUCCESS;
}
