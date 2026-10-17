#include "support/spindle_sync_motion_host.h"
int main(void)
{
    prepare_spindle_sync_motion();
    sync_motion_feedback.rpm = 0;
    queue_motion_program("G95G1Z1F1");
    state_set(STATE_CYCLE);
    CHECK(state_get() == STATE_ALARM && sys.alarm == Alarm_Spindle);
    CHECK(wake_calls == 0 && axis_pulses[Z_AXIS] == 0);
    CHECK(physical_position[Z_AXIS] == 0 && sync_encoder_resets == 0);
    CHECK(sync_rpm_reads > 0 && sync_angle_reads == 0);
    return EXIT_SUCCESS;
}
