#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); queue_spindle_sync_line(10,false); execute_motion_program();
    CHECK(axis_pulses[Z_AXIS]==800); CHECK(physical_position[Z_AXIS]==800); CHECK(sys.position[Z_AXIS]==800);
    CHECK(axis_pulses[X_AXIS]==0); CHECK(axis_pulses[Y_AXIS]==0); CHECK(sync_rpm_reads>0); CHECK(sync_angle_reads>0);
    return EXIT_SUCCESS;
}
