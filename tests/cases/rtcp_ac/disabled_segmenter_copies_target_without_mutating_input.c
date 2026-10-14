#include "support/rtcp_host.h"

int main(void)
{
    prepare_rtcp();
    coord_data_t target = {.x = 1, .y = 2, .z = 3, .a = 4, .c = 5}, position = {0};
    plan_line_data_t data = {.feed_rate = 123};
    coord_data_t *segment = kinematics.segment_line(&target, &position, &data, true);
    CHECK(segment && segment != &target);
    for(unsigned i = 0; i < N_AXIS; i++) NEAR(segment->values[i], target.values[i]);
    CHECK(kinematics.segment_line(&target, &position, &data, false) != NULL);
    CHECK(kinematics.segment_line(&target, &position, &data, false) == NULL);
    NEAR(data.feed_rate, 123); NEAR(target.x, 1); NEAR(position.x, 0);
    return EXIT_SUCCESS;
}
