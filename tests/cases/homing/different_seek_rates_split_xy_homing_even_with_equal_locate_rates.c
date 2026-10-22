#include "support/homing_host.h"

int main(void)
{
    prepare_homing();
    settings.homing.flags.per_axis_feedrates = true;
    settings.axis[Y_AXIS].homing_seek_rate = 200;
    CHECK(mc_homing_cycle((axes_signals_t){.mask = 3}) == Status_OK);
    CHECK(sys.homed.mask == 3);
    CHECK(physical_position[0] == 70);
    CHECK(axis_pulses[0] == 110);
    CHECK(physical_position[1] == 110);
    CHECK(axis_pulses[1] == 150);
    CHECK(physical_position[2] == 0 && axis_pulses[2] == 0);
    CHECK(limit_enable_calls == 3);
    CHECK(completed_calls == 1 && homing_success);
    return EXIT_SUCCESS;
}
