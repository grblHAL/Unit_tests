#include "support/backlash_host.h"

int main(void)
{
    prepare_backlash();
    CHECK(sys.driver_started && settings.axis[X_AXIS].backlash > 0);
    settings_restore((settings_restore_t){.defaults = true});
    NEAR(settings.axis[X_AXIS].backlash, 0);
    queue_motion_program("G1X1F100");
    execute_motion_program();
    int32_t expected = lroundf(settings.axis[X_AXIS].steps_per_mm);
    CHECK(sys.position[X_AXIS] == expected);
    CHECK(axis_pulses[X_AXIS] == (unsigned)expected);
    CHECK(physical_position[X_AXIS] == expected);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
