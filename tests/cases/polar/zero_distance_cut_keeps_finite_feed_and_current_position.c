#include "support/polar_segment_host.h"

int main(void)
{
    prepare_polar_segments();
    coord_data_t target = {.x = 10, .z = 3};
    coord_data_t start = polar_start_at(target);
    plan_line_data_t data = {.feed_rate = 100, .rate_multiplier = 1};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    coord_data_t *joint = kinematics.segment_line(&target, NULL, &data, false);
    CHECK(joint != NULL);
    for(unsigned axis = 0; axis < N_AXIS; axis++) NEAR(joint->values[axis], start.values[axis]);
    CHECK(kinematics.segment_line(&target, NULL, &data, false) == NULL);
    NEAR(data.feed_rate, 100);
    NEAR(data.rate_multiplier, 1);
    return EXIT_SUCCESS;
}
