#include "support/ganging_host.h"

int main(void)
{
    prepare_ganging();
    for(unsigned i = 0; i < N_AXIS; i++)
        CHECK(kinematics.limits_get_axis_mask(i) == (1u << i));
    CHECK(kinematics.homing_cycle_validate((axes_signals_t){.mask = Y_AXIS_BIT | (1u << 3)}));
    return EXIT_SUCCESS;
}
