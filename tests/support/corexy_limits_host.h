#pragma once
#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "machine_limits.h"
#include "check.h"
void corexy_init(void);
static inline void prepare_corexy_limits(void)
{
    engine_prepare();
    limits_init();
    corexy_init();
    sys.homed.mask = AXES_BITMASK;
    coord_data_t pulloff = {.values = {1, 2, 3}};
    limits_homing_pulloff(&pulloff);
    sys.position[X_AXIS] = 1040;
    sys.position[Y_AXIS] = 560;
    sys.position[Z_AXIS] = -160;
}
