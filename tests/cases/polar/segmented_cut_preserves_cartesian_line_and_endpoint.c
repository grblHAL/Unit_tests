#include "support/polar_segment_host.h"

int main(void)
{
    prepare_polar_segments();
    coord_data_t start = polar_start_at((coord_data_t){.x = 10});
    coord_data_t target = {.x = 10, .y = 2, .z = 3};
    plan_line_data_t data = {.feed_rate = 100};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    coord_data_t previous = {.x = 10}, final = {0};
    unsigned segments = 0;
    coord_data_t *joint;
    while((joint = kinematics.segment_line(&target, NULL, &data, false))) {
        CHECK(++segments < 50);
        final = polar_cartesian(joint);
        CHECK(fabsf(final.x - 10) < 0.0001f);
        CHECK(fabsf(final.z - 1.5f * final.y) < 0.0001f);
        float dx = final.x - previous.x, dy = final.y - previous.y, dz = final.z - previous.z;
        CHECK(sqrtf(dx * dx + dy * dy + dz * dz) <= 0.5001f);
        CHECK(data.feed_rate > 0 && isfinite(data.feed_rate));
        CHECK(data.rate_multiplier > 0 && isfinite(data.rate_multiplier));
        previous = final;
        data.feed_rate = 100; /* mc_line supplies the programmed feed for each segment. */
    }
    CHECK(segments > 1);
    CHECK(fabsf(final.x - target.x) < 0.0001f);
    CHECK(fabsf(final.y - target.y) < 0.0001f);
    NEAR(final.z, target.z);
    return EXIT_SUCCESS;
}
