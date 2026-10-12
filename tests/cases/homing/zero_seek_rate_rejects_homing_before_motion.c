#include "support/homing_host.h"
#include "check.h"

int main(void)
{
    prepare_homing();
    settings.axis[X_AXIS].homing_seek_rate = 0;
    CHECK(mc_homing_cycle((axes_signals_t){.mask = X_AXIS_BIT}) == Status_HomingDisabled);
    CHECK(wake_calls == 0);
    CHECK(limit_enable_calls == 0);
    CHECK(completed_calls == 0);
    CHECK(sys.homed.mask == 0);
    return EXIT_SUCCESS;
}
