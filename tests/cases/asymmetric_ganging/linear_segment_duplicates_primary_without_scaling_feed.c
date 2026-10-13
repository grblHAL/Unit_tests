#include "support/ganging_host.h"

int main(void)
{
    prepare_ganging();
    coord_data_t target = {.values = {2, -3, 4, 99}}, position = {0};
    plan_line_data_t data = {.feed_rate = 123};
    coord_data_t *segment = kinematics.segment_line(&target, &position, &data, true);
    CHECK(segment != NULL);
    NEAR(segment->values[0], 2); NEAR(segment->values[1], -3);
    NEAR(segment->values[2], 4); NEAR(segment->values[3], -3);
    NEAR(data.feed_rate, 123); NEAR(target.values[3], 99);
    CHECK(kinematics.segment_line(&target, &position, &data, false) != NULL);
    CHECK(kinematics.segment_line(&target, &position, &data, false) == NULL);
    return EXIT_SUCCESS;
}
