#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "machine_limits.h"
#include "check.h"
void corexy_init(void);
int main(void)
{
    engine_prepare();
    limits_init();
    corexy_init();
    CHECK(kinematics.homing_cycle_validate((axes_signals_t){.mask = X_AXIS_BIT}));
    CHECK(kinematics.homing_cycle_validate((axes_signals_t){.mask = Y_AXIS_BIT}));
    CHECK(kinematics.homing_cycle_validate((axes_signals_t){.mask = Z_AXIS_BIT}));
    CHECK(!kinematics.homing_cycle_validate((axes_signals_t){.mask = X_AXIS_BIT | Y_AXIS_BIT}));
    return EXIT_SUCCESS;
}
