#include "support/backlash_host.h"

int main(void)
{
    prepare_backlash();
    settings_restore((settings_restore_t){.parameters = true});
    NEAR(settings.axis[X_AXIS].backlash, .1f);
    queue_motion_program("G1X1F100");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(axis_pulses[X_AXIS] == 88 && physical_position[X_AXIS] == 88);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
