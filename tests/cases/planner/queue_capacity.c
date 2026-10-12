#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); plan_line_data_t data = {.feed_rate = 100}; float target[N_AXIS] = {0};
    for(unsigned i = 1; i <= 16; i++) { target[0] = (float)i; CHECK(!plan_check_full_buffer()); CHECK(plan_buffer_line(target, &data)); }
    CHECK(plan_check_full_buffer()); CHECK(plan_get_block_buffer_available() == 0);
    plan_discard_current_block(); CHECK(!plan_check_full_buffer()); CHECK(plan_get_block_buffer_available() == 1);
    return EXIT_SUCCESS;
}
