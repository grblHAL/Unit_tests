#include "support/rtcp_host.h"
int main(void)
{
    prepare_rtcp();
    CHECK(kinematics.homing_cycle_validate((axes_signals_t){.mask = X_AXIS_BIT}));
    CHECK(kinematics.homing_cycle_validate((axes_signals_t){.mask = A_AXIS_BIT | C_AXIS_BIT}));
    CHECK(kinematics.homing_cycle_validate((axes_signals_t){.mask = AXES_BITMASK}));
    return EXIT_SUCCESS;
}
