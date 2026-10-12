#include "support/laser_stepper_host.h"
#include "check.h"

int main(void)
{
    prepare_laser_stepper(); plan_line_data_t data; plan_data_init(&data);
    data.feed_rate=100; data.spindle.state.on=true; data.spindle.rpm=250; float target[N_AXIS]={0};
    state_set(STATE_CHECK_MODE); CHECK(mc_line(target,&data)==Status_Handled);
    CHECK(laser_output_calls==0); CHECK(plan_get_current_block()==NULL); CHECK(wake_calls==0);
    return EXIT_SUCCESS;
}
