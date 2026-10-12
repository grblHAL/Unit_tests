#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); plan_line_data_t data = {.feed_rate = 100}; float target[N_AXIS] = {3, 4, 0};
    CHECK(plan_buffer_line(target, &data)); plan_block_t *block = plan_get_current_block(); CHECK(block != NULL);
    NEAR(block->millimeters, 5); CHECK(block->steps.value[0] == 240); CHECK(block->steps.value[1] == 320); NEAR(block->rapid_rate, 1250);
    return EXIT_SUCCESS;
}
