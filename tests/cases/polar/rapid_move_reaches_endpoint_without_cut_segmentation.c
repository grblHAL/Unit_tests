#include "support/polar_segment_host.h"

int main(void)
{
    prepare_polar_segments();
    coord_data_t start = polar_start_at((coord_data_t){.x = 10});
    coord_data_t target = {.x = 20, .y = 2, .z = 3};
    plan_line_data_t data = {.feed_rate = 100, .rate_multiplier = 1,
        .condition = {.rapid_motion = true}};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    coord_data_t *joint = kinematics.segment_line(&target, NULL, &data, false);
    CHECK(joint != NULL);
    coord_data_t final = polar_cartesian(joint);
    CHECK(fabsf(final.x - target.x) < 0.0001f);
    CHECK(fabsf(final.y - target.y) < 0.0001f);
    NEAR(final.z, target.z);
    CHECK(kinematics.segment_line(&target, NULL, &data, false) == NULL);
    NEAR(data.feed_rate, 100);
    NEAR(data.rate_multiplier, 1);
    return EXIT_SUCCESS;
}
