#include "support/polar_segment_host.h"

int main(void)
{
    prepare_polar_segments();
    coord_data_t start = polar_start_at((coord_data_t){
        .x = 10 * cosf(-RADDEG), .y = 10 * sinf(-RADDEG)});
    coord_data_t target = {.x = 10 * cosf(RADDEG), .y = 10 * sinf(RADDEG)}, joint;
    kinematics.transform_from_cartesian(&joint, &target);
    CHECK(fabsf(joint.y - start.y - 2) < 0.001f);
    CHECK(fabsf(joint.y - 1) < 0.001f);
    CHECK(fabsf(joint.x - 10) < 0.0001f);
    return EXIT_SUCCESS;
}
