#include "support/rtcp_host.h"
#include "machine_limits.h"
int main(void)
{
    prepare_rtcp();
    float rate = kinematics.homing_cycle_get_feedrate((axes_signals_t){.mask=A_AXIS_BIT | Z_AXIS_BIT},25.25f,HomingMode_Locate);
    NEAR(rate,25.25f);
    return EXIT_SUCCESS;
}
