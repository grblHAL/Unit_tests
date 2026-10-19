#include "support/partial_peck_motion_host.h"
int main(void)
{
    prepare_partial_peck_motion();
    char retract[] = "0.1";
    CHECK(settings_store_setting(Setting_G73Retract, retract) == Status_OK);
    execute_canned("G99G73X1Z-1.25R0Q0.5F100");
    CHECK(partial_peck_deepest_z == -100);
    CHECK(physical_position[Z_AXIS] == 0 && sys.position[Z_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 232);
    CHECK(physical_position[X_AXIS] == 80 && axis_pulses[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
