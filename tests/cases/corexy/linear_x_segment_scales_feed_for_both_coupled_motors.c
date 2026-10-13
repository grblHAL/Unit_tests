#include "support/corexy_limits_host.h"

int main(void)
{
    prepare_corexy_limits();
    coord_data_t position = {.values = {13, 7, -2}};
    coord_data_t target = {.values = {11, 3, -2}};
    plan_line_data_t data = {.feed_rate = 100};
    coord_data_t *segment = kinematics.segment_line(&target, &position, &data, true);
    CHECK(segment != NULL);
    NEAR(segment->x, 14); NEAR(segment->y, 8); NEAR(segment->z, -2);
    NEAR(data.feed_rate, 141.421356f);
    float scaled_feed = data.feed_rate;
    CHECK(kinematics.segment_line(&target, &position, &data, false) != NULL);
    CHECK(kinematics.segment_line(&target, &position, &data, false) == NULL);
    NEAR(data.feed_rate, scaled_feed);
    NEAR(position.x, 13); NEAR(position.y, 7); NEAR(position.z, -2);
    return EXIT_SUCCESS;
}
