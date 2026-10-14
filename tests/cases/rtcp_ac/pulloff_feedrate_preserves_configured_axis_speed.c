#include "support/rtcp_host.h"
#include "machine_limits.h"
int main(void)
{
    prepare_rtcp();
    float rate = kinematics.homing_cycle_get_feedrate((axes_signals_t){.mask=A_AXIS_BIT | Z_AXIS_BIT},50.75f,HomingMode_Pulloff);
    NEAR(rate,50.75f);
    return EXIT_SUCCESS;
}
