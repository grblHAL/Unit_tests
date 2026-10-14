#include "support/wall_host.h"

int main(void)
{
    prepare_wall();
    coord_data_t start = {.x = 125, .y = 125}, target = {.x = 106, .y = 75, .z = 9};
    plan_line_data_t data = {.feed_rate = 100};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    for(unsigned i = 1; i <= 3; i++) {
        coord_data_t *segment = kinematics.segment_line(&target, &start, &data, false);
        CHECK(segment); NEAR(segment->z, 3 * i);
    }
    CHECK(kinematics.segment_line(&target, &start, &data, false) == NULL);
    NEAR(target.z, 9); NEAR(data.feed_rate, 100);
    return EXIT_SUCCESS;
}
