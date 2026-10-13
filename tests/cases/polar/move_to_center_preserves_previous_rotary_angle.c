#include "support/polar_segment_host.h"

int main(void)
{
    prepare_polar_segments();
    coord_data_t start = polar_start_at((coord_data_t){.y = 10});
    coord_data_t target = {.z = 3}, joint;
    CHECK(kinematics.transform_from_cartesian(&joint, &target) == &joint);
    NEAR(joint.x, 0);
    NEAR(joint.y, start.y);
    NEAR(joint.z, 3);
    return EXIT_SUCCESS;
}
