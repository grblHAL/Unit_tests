#include "support/backlash_settings_host.h"
int main(void)
{
    prepare_motion_program();
    char value[] = "0.1";
    CHECK(settings_store_setting(Setting_AxisBacklash + Z_AXIS, value) == Status_OK);
    queue_motion_program("G1Z-1F100");
    queue_motion_program("G1Z0");
    execute_motion_program();
    CHECK(axis_pulses[Z_AXIS] == 168);
    CHECK(sys.position[Z_AXIS] == 0);
    CHECK(physical_position[Z_AXIS] == 8);
    CHECK(axis_pulses[X_AXIS] == 0 && axis_pulses[Y_AXIS] == 0);
    NEAR(gc_state.position[Z_AXIS], 0.0f);
    return EXIT_SUCCESS;
}
