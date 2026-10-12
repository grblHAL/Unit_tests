#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    stuck_after_contact = true;
    CHECK(mc_homing_cycle((axes_signals_t){.bits = 1}) == Status_Unhandled);
    CHECK(sys.alarm == Alarm_FailPulloff);
    CHECK(sys.homed.bits == 0);
    CHECK(reset_calls == 1);
    CHECK(!homing_success);
    return EXIT_SUCCESS;
}
