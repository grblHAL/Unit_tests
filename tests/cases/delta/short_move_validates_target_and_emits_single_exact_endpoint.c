#include "support/delta_host.h"

int main(void)
{
    prepare_delta();
    coord_data_t initial = {.z = -300}, start;
    coord_data_t target = {.x = .01f, .z = -300};
    kinematics.transform_from_cartesian(&start, &initial);
    plan_line_data_t data = {.feed_rate = 100};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    CHECK(data.condition.target_validated && data.condition.target_valid);
    coord_data_t *segment = kinematics.segment_line(&target, &start, &data, false);
    CHECK(segment != NULL);
    coord_data_t endpoint = *segment;
    CHECK(isfinite(data.feed_rate) && data.feed_rate > 0);
    CHECK(kinematics.segment_line(&target, &start, &data, false) == NULL);

    mpos_t steps;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        settings.axis[axis].steps_per_mm = 1000000;
        steps.values[axis] = lroundf(endpoint.values[axis] * settings.axis[axis].steps_per_mm);
    }
    coord_data_t final;
    kinematics.transform_steps_to_cartesian(&final, &steps);
    CHECK(fabsf(final.x - target.x) < .001f);
    CHECK(fabsf(final.y - target.y) < .001f);
    CHECK(fabsf(final.z - target.z) < .001f);
    return EXIT_SUCCESS;
}
