#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); plan_line_data_t data = {.feed_rate = 100, .line_number = 1}; float first[N_AXIS] = {1, 0, 0};
    CHECK(plan_buffer_line(first, &data)); data.line_number = 2; float next[N_AXIS] = {2, 0, 0}; CHECK(plan_buffer_line(next, &data));
    CHECK(plan_get_current_block()->line_number == 1); CHECK(plan_get_recent_block()->line_number == 2);
    plan_discard_current_block(); CHECK(plan_get_current_block()->line_number == 2); plan_discard_current_block(); CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
