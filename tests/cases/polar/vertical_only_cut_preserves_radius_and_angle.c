#include "support/polar_segment_host.h"

int main(void)
{
    prepare_polar_segments();
    coord_data_t start = polar_start_at((coord_data_t){.x = 10});
    coord_data_t target = {.x = 10, .z = 5};
    plan_line_data_t data = {.feed_rate = 100};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    coord_data_t *joint = kinematics.segment_line(&target, NULL, &data, false);
    CHECK(joint != NULL);
    NEAR(joint->x, start.x); NEAR(joint->y, start.y); NEAR(joint->z, 5);
    CHECK(kinematics.segment_line(&target, NULL, &data, false) == NULL);
    NEAR(data.feed_rate, 100);
    return EXIT_SUCCESS;
}
