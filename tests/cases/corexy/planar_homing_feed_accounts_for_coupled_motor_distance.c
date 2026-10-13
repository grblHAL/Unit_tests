#include "support/corexy_limits_host.h"

int main(void)
{
    prepare_corexy_limits();
    for(unsigned mode = HomingMode_Seek; mode <= HomingMode_Pulloff; mode++) {
        NEAR(kinematics.homing_cycle_get_feedrate((axes_signals_t){.mask = X_AXIS_BIT}, 100,
                                                 (homing_mode_t)mode), 141.421356f);
        NEAR(kinematics.homing_cycle_get_feedrate((axes_signals_t){.mask = Y_AXIS_BIT}, 100,
                                                 (homing_mode_t)mode), 141.421356f);
    }
    return EXIT_SUCCESS;
}
