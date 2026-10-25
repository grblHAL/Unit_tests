#include "support/vfd_css_motion_host.h"
#include "support/named_parameter_host.h"
int main(void)
{
    prepare_vfd_css_motion();
    vfd_block("G97M3S300");
    vfd_block("M70");
    vfd_block("G96S100D900");
    vfd_block("M72");
    CHECK(gc_spindle_get(0)->rpm_mode == SpindleSpeedMode_RPM);
    NEAR(read_named_parameter("_spindle_rpm_mode"), 1);
    NEAR(vfd_live_rpm, 300);
    vfd_check_fixed_rpm = true;
    vfd_expected_fixed_rpm = 300;
    queue_motion_program("G1X20F100");
    execute_motion_program();
    CHECK(protocol_exec_rt_system());
    CHECK(physical_position[X_AXIS] == 1600 && axis_pulses[X_AXIS] == 1600);
    CHECK(axis_pulses[Y_AXIS] == 0 && axis_pulses[Z_AXIS] == 0);
    NEAR(vfd_live_rpm, 300);
    CHECK(vfd_state.on && !sys.abort && sys.alarm == Alarm_None);
    ngc_modal_state_invalidate();
    return EXIT_SUCCESS;
}
