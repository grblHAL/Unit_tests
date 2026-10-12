#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); plan_line_data_t data = {.feed_rate = 100}; float target[N_AXIS] = {10, 0, 0};
    CHECK(plan_buffer_line(target, &data)); plan_block_t *block = plan_get_current_block(); CHECK(block != NULL);
    CHECK(block->steps.value[0] == 800); CHECK(block->steps.value[1] == 0); CHECK(block->step_event_count == 800);
    NEAR(block->millimeters, 10); CHECK(block->direction.mask == 0); NEAR(block->entry_speed_sqr, 0);
    return EXIT_SUCCESS;
}
