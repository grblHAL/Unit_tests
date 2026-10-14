#pragma once
#include "support/rtcp_host.h"
static unsigned complete_rtcp_segment(coord_data_t *target, coord_data_t *last)
{
    coord_data_t position = {0};
    plan_line_data_t data = {.feed_rate = 100};
    CHECK(kinematics.segment_line(target, &position, &data, true) != NULL);
    unsigned count = 0;
    coord_data_t *segment;
    while((segment = kinematics.segment_line(target, &position, &data, false))) {
        CHECK(++count <= 1000);
        *last = *segment;
    }
    CHECK(count > 0);
    NEAR(data.feed_rate, 100);
    return count;
}
