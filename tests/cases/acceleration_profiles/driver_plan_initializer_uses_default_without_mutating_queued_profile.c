#include "support/motion_program_host.h"
#include "motion_control.h"
#include "check.h"

int main(void)
{
    prepare_motion_program();
    settings.axis[X_AXIS].acceleration = 36000;
    queue_motion_program("G187P5G1X10F100");
    plan_block_t *profiled = plan_get_current_block();
    CHECK(profiled != NULL);
    NEAR(profiled->acceleration, 7200);
    plan_line_data_t data;
    plan_data_init(&data);
    NEAR(data.acceleration_factor, 1);
    data.feed_rate = 100;
    float target[N_AXIS] = {20};
    CHECK(mc_line(target, &data) == Status_Handled);
    plan_block_t *driver = plan_get_recent_block();
    CHECK(driver != NULL && driver != profiled);
    NEAR(driver->acceleration, 36000);
    NEAR(driver->target_mm[X_AXIS], 20);
    CHECK(driver->steps.value[X_AXIS] == 800);
    NEAR(profiled->acceleration, 7200);
    NEAR(gc_state.modal.acceleration_factor, 0.2f);
    return EXIT_SUCCESS;
}
