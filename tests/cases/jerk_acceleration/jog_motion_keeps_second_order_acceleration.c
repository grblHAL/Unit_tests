#include "support/motion_program_host.h"
#include "check.h"

int main(void)
{
    prepare_motion_program(); settings.axis[X_AXIS].acceleration=100; settings.axis[X_AXIS].jerk=1;
    float target[N_AXIS]={10,0,0}; plan_line_data_t data; plan_data_init(&data); data.feed_rate=100;
    data.condition.jog_motion=true;
    CHECK(plan_buffer_line(target,&data)); plan_block_t *block=plan_get_current_block(); CHECK(block != NULL);
    CHECK(!block->condition.jerk); NEAR(block->acceleration,100); CHECK(block->steps.value[X_AXIS]==800);
    return EXIT_SUCCESS;
}
