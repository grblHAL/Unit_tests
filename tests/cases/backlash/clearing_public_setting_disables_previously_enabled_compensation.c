#include "support/backlash_settings_host.h"

int main(void)
{
    prepare_backlash();
    CHECK(store_backlash("0") == Status_OK);
    CHECK(settings.axis[X_AXIS].backlash == 0);
    queue_motion_program("G1X1F100"); execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80);
    if(axis_pulses[X_AXIS] != 80)
        fprintf(stderr, "Zero backlash: expected 80 X pulses, observed %u\n", axis_pulses[X_AXIS]);
    CHECK(axis_pulses[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
