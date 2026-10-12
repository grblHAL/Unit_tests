#include "support/spindle_sync_motion_host.h"
#include "check.h"

int main(void)
{
    prepare_spindle_sync_motion(); queue_spindle_sync_line(10,false);
    float target[N_AXIS]={0,0,20}; plan_line_data_t data; plan_data_init(&data); data.feed_rate=100; CHECK(plan_buffer_line(target,&data));
    execute_motion_program(); CHECK(hal.stepper.pulse_start==sync_motion_pulse);
    CHECK(axis_pulses[Z_AXIS]==1600); CHECK(physical_position[Z_AXIS]==1600); CHECK(sys.position[Z_AXIS]==1600);
    return EXIT_SUCCESS;
}
