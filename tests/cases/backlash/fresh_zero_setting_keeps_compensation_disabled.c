#include "support/backlash_settings_host.h"

int main(void)
{
    prepare_motion_program();
    CHECK(store_backlash("0") == Status_OK);
    queue_motion_program("G1X1F100"); execute_motion_program();
    CHECK(settings.axis[X_AXIS].backlash == 0);
    CHECK(axis_pulses[X_AXIS] == 80 && sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
