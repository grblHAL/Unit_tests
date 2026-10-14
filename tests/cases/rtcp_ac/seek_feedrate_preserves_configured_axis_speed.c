#include "support/rtcp_host.h"
#include "machine_limits.h"
int main(void)
{
    prepare_rtcp();
    float rate = kinematics.homing_cycle_get_feedrate((axes_signals_t){.mask=A_AXIS_BIT | Z_AXIS_BIT},125.5f,HomingMode_Seek);
    NEAR(rate,125.5f);
    return EXIT_SUCCESS;
}
