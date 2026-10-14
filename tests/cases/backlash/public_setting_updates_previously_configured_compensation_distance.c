#include "support/backlash_settings_host.h"

int main(void)
{
    prepare_backlash();
    CHECK(store_backlash("0.2") == Status_OK);
    queue_motion_program("G1X1F100"); execute_motion_program();
    CHECK(settings.axis[X_AXIS].backlash == .2f);
    CHECK(axis_pulses[X_AXIS] == 96 && sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
