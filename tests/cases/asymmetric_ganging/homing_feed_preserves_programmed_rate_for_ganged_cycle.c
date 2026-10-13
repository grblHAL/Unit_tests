#include "support/ganging_host.h"
#include "machine_limits.h"

int main(void)
{
    prepare_ganging();
    for(unsigned mode = HomingMode_Seek; mode <= HomingMode_Pulloff; mode++)
        NEAR(kinematics.homing_cycle_get_feedrate((axes_signals_t){.mask = Y_AXIS_BIT | (1u << 3)},
                                                 75, (homing_mode_t)mode), 75);
    return EXIT_SUCCESS;
}
