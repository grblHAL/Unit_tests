#include "support/motion_program_host.h"

int main(void)
{
    prepare_motion_program();
    settings.axis[X_AXIS].acceleration = 36000;
    queue_motion_program("G187P2G1X1F100");
    plan_block_t *first = plan_get_current_block();
    unsigned available = plan_get_block_buffer_available();
    char invalid[] = "G187.1P5G20G91X1";
    CHECK(gc_execute_block(invalid) == Status_GcodeUnsupportedCommand);
    CHECK(plan_get_current_block() == first);
    CHECK(plan_get_block_buffer_available() == available);
    CHECK(!gc_state.modal.units_imperial && !gc_state.modal.distance_incremental);
    NEAR(gc_state.position[X_AXIS], 1);
    NEAR(first->acceleration, 28800);
    queue_motion_program("G1X2");
    NEAR(plan_get_recent_block()->acceleration, 28800);
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 160 && physical_position[X_AXIS] == 160);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
