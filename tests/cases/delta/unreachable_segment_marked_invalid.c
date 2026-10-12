#include "support/delta_host.h"
#include "check.h"

int main(void)
{
    prepare_delta();
    sys.soft_limits.bits = 7;
    coord_data_t target = {.x = 1000, .y = 1000, .z = -300}, start = {0};
    plan_line_data_t data = {0};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    CHECK(data.condition.target_validated);
    CHECK(!data.condition.target_valid);
    return EXIT_SUCCESS;
}
