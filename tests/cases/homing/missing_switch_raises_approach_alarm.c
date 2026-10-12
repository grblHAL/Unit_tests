#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    switch_position[X_AXIS] = 10000;
    CHECK(mc_homing_cycle((axes_signals_t){.bits = 1}) == Status_Unhandled);
    CHECK(sys.alarm == Alarm_HomingFailApproach);
    CHECK(sys.homed.bits == 0);
    CHECK(sys.abort);
    CHECK(reset_calls == 1);
    CHECK(completed_calls == 1);
    CHECK(!homing_success);
    return EXIT_SUCCESS;
}
