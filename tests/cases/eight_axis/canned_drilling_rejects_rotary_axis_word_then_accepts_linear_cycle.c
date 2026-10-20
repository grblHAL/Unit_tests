#include "support/canned_motion_host.h"

int main(void)
{
    prepare_canned_motion();
    char rotary[] = "1";
    CHECK(settings_store_setting(Settings_RotaryAxes, rotary) == Status_OK);
    CHECK(settings.steppers.is_rotary.mask & bit(A_AXIS));
    CHECK(canned_block("G81X1Z-1R0A45F100") == Status_GcodeAxisCommandConflict);
    CHECK(plan_get_current_block() == NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++)
        CHECK(physical_position[axis] == 0 && axis_pulses[axis] == 0);
    execute_canned("G81X1Z-1R0F100");
    CHECK(physical_position[X_AXIS] == 80 && physical_position[Z_AXIS] == 0);
    CHECK(physical_position[A_AXIS] == 0 && axis_pulses[A_AXIS] == 0);
    CHECK(axis_pulses[Z_AXIS] == 160);
    return EXIT_SUCCESS;
}
