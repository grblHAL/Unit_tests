#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    settings.homing.flags.per_axis_feedrates = true;
    settings.axis[Y_AXIS].homing_seek_rate = 200;
    settings.axis[Y_AXIS].homing_feed_rate = 50;
    CHECK(mc_homing_cycle((axes_signals_t){.bits = 3}) == Status_OK);
    CHECK(sys.homed.bits == 3);
    CHECK(physical_position[X_AXIS] == 70);
    CHECK(physical_position[Y_AXIS] == 110);
    CHECK(axis_pulses[X_AXIS] == 110);
    CHECK(axis_pulses[Y_AXIS] == 150);
    CHECK(limit_enable_calls == 3);
    return EXIT_SUCCESS;
}
