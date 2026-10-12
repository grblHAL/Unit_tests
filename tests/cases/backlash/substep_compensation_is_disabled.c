#include "support/backlash_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    settings.axis[X_AXIS].backlash = .001f;
    mc_backlash_init((axes_signals_t){.bits = 1u << X_AXIS});
    queue_motion_program("G1X1F100");
    execute_motion_program();
    CHECK(axis_pulses[X_AXIS] == 80);
    CHECK(sys.position[X_AXIS] == 80);
    return EXIT_SUCCESS;
}
