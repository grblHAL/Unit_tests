#include "support/rtcp_host.h"

int main(void)
{
    prepare_rtcp();
    for(unsigned i = 0; i < N_AXIS; i++) sys.position[i] = 100 + i;
    kinematics.limits_set_target_pos(C_AXIS);
    for(unsigned i = 0; i < N_AXIS; i++) CHECK(sys.position[i] == (i == C_AXIS ? 0 : 100 + (int)i));
    return EXIT_SUCCESS;
}
