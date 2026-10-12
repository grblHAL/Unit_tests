#include "support/backlash_host.h"
#include "check.h"

int main(void)
{
    prepare_backlash();
    settings.axis[Y_AXIS].backlash = .05f;
    mc_backlash_init((axes_signals_t){.bits = 1u << Y_AXIS});
    queue_motion_program("G1X1Y1F100");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 88);
    CHECK(axis_pulses[Y_AXIS] == 84);
    CHECK(sys.position[X_AXIS] == 80);
    CHECK(sys.position[Y_AXIS] == 80);
    return EXIT_SUCCESS;
}
