#include "support/laser_stepper_host.h"
#include "check.h"
static unsigned ordered_power_changes;
static void execute_laser_motion(sys_state_t state)
{
    if(state==STATE_CYCLE) { st_prep_buffer(); stepper_driver_interrupt_handler(); }
}
static void ordered_laser_output(spindle_ptrs_t *spindle, spindle_state_t state, float rpm)
{
    if(rpm==250) {
        CHECK(plan_get_current_block()==NULL); CHECK(physical_position[X_AXIS]==80);
        ordered_power_changes++;
    }
    laser_output(spindle,state,rpm);
}
int main(void)
{
    prepare_laser_stepper(); grbl.on_execute_realtime=execute_laser_motion; spindle_get(0)->set_state=ordered_laser_output;
    plan_line_data_t data; plan_data_init(&data); data.feed_rate=100; data.spindle.state.on=true; data.spindle.rpm=100;
    float target[N_AXIS]={1,0,0}; CHECK(mc_line(target,&data)==Status_Handled); CHECK(plan_get_current_block()!=NULL);
    data.spindle.rpm=250; CHECK(mc_line(target,&data)==Status_Handled);
    CHECK(ordered_power_changes==1); NEAR(laser_output_power,250); CHECK(physical_position[X_AXIS]==80); CHECK(axis_pulses[X_AXIS]==80);
    CHECK(plan_get_current_block()==NULL); CHECK(state_get()==STATE_IDLE);
    return EXIT_SUCCESS;
}
