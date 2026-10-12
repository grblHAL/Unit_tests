#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); plan_line_data_t data = {.feed_rate = 100}; float target[N_AXIS] = {0};
    CHECK(!plan_buffer_line(target, &data)); CHECK(plan_get_current_block() == NULL); CHECK(plan_get_block_buffer_available() == 16);
    return EXIT_SUCCESS;
}
