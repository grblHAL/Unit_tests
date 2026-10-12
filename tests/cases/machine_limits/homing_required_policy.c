#include "support/control_host.h"
#include "check.h"

int main(void)
{
    settings.homing.flags.enabled = 1; settings.homing.flags.init_lock = 1; sys.homing.mask = 3;
    CHECK(limits_homing_required()); sys.homed.mask = 3; CHECK(!limits_homing_required());
    sys.homed.mask = 1; settings.homing.flags.override_locks = 1; CHECK(!limits_homing_required());
    sys.cold_start = true; CHECK(limits_homing_required()); settings.homing.flags.enabled = 0; CHECK(!limits_homing_required());
    return EXIT_SUCCESS;
}
