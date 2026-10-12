#include "support/delta_host.h"
#include "check.h"

int main(void)
{
    prepare_delta();
    coord_data_t target = {.x = 1, .y = 0, .z = -300}, initial = {.z = -300}, start;
    kinematics.transform_from_cartesian(&start, &initial);
    plan_line_data_t data = {.feed_rate = 100, .condition = {.target_validated = true, .target_valid = true}};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    coord_data_t last = {0};
    unsigned segments = 0;
    coord_data_t *segment;
    while((segment = kinematics.segment_line(&target, &start, &data, false)) != NULL) {
        CHECK(++segments < 10);
        last = *segment;
    }
    CHECK(segments >= 5);
    mpos_t steps;
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        settings.axis[axis].steps_per_mm = 1000000;
        steps.values[axis] = lroundf(last.values[axis] * settings.axis[axis].steps_per_mm);
    }
    coord_data_t final;
    kinematics.transform_steps_to_cartesian(&final, &steps);
    CHECK(fabsf(final.x - target.x) < .001f);
    CHECK(fabsf(final.y - target.y) < .001f);
    CHECK(fabsf(final.z - target.z) < .001f);
    return EXIT_SUCCESS;
}
