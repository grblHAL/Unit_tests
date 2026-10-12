#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); settings.position.pid.p_gain=0.5f;
    grbl.on_settings_changed(&settings,(settings_changed_flags_t){0});
    float target[N_AXIS]={0,0,10}; plan_line_data_t data; plan_data_init(&data); data.feed_rate=0.1f;
    data.spindle.state.synchronized=true; CHECK(plan_buffer_line(target,&data)); execute_motion_program();
    CHECK(sync_angle_reads>1); CHECK(axis_pulses[Z_AXIS]==800); CHECK(physical_position[Z_AXIS]==800);
    CHECK(sys.position[Z_AXIS]==800); CHECK(sync_timer_cycles>0);
    return EXIT_SUCCESS;
}
