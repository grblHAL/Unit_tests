#include "support/engine_host.h"
#include "check.h"

int main(void)
{
    engine_prepare(); CHECK(plan_reset()); plan_line_data_t data = {.condition.rapid_motion = 1}; float target[N_AXIS] = {10, 0, 0};
    CHECK(plan_buffer_line(target, &data)); NEAR(plan_get_current_block()->programmed_rate, 1000);
    return EXIT_SUCCESS;
}
