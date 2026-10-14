#include "support/rtcp_host.h"
#include "machine_limits.h"

int main(void)
{
    prepare_rtcp();
    coord_data_t pulloff = {.z = 2}; limits_homing_pulloff(&pulloff);
    for(unsigned i = 0; i < N_AXIS; i++) sys.position[i] = 100 + i;
    kinematics.limits_set_machine_positions((axes_signals_t){.mask = Z_AXIS_BIT});
    for(unsigned i = 0; i < N_AXIS; i++) CHECK(sys.position[i] == (i == Z_AXIS ? -160 : 100 + (int)i));
    return EXIT_SUCCESS;
}
