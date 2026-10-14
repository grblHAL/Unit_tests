#include "support/wall_host.h"

int main(void)
{
    prepare_wall();
    coord_data_t start = {.x = 125, .y = 125}, target = {.x = 101, .y = 75};
    plan_line_data_t data = {.feed_rate = 100};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    coord_data_t *result = kinematics.segment_line(&target, &start, &data, false);
    CHECK(result != NULL);
    CHECK(fabsf(result->x - hypotf(101, 75)) < .0001f);
    CHECK(fabsf(result->y - hypotf(99, 75)) < .0001f);
    CHECK(kinematics.segment_line(&target, &start, &data, false) == NULL);
    NEAR(data.feed_rate, 100);
    return EXIT_SUCCESS;
}
