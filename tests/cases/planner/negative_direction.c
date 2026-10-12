#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); plan_line_data_t data = {.feed_rate = 100}; float target[N_AXIS] = {-10, 0, -5};
    CHECK(plan_buffer_line(target, &data)); plan_block_t *block = plan_get_current_block(); CHECK(block != NULL);
    CHECK(block->direction.mask == 5); CHECK(block->steps.value[0] == 800); CHECK(block->steps.value[2] == 400);
    return EXIT_SUCCESS;
}
