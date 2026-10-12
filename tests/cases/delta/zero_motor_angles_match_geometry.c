#include "support/delta_host.h"
#include "check.h"

int main(void)
{
    prepare_delta();
    mpos_t steps = {0};
    coord_data_t result;
    kinematics.transform_steps_to_cartesian(&result, &steps);
    float radial = 100 + (75 - 24) / (2 * sqrtf(3));
    float expected_z = -sqrtf(300 * 300 - radial * radial);
    CHECK(fabsf(result.x) < .0001f);
    CHECK(fabsf(result.y) < .0001f);
    CHECK(fabsf(result.z - expected_z) < .0001f);
    return EXIT_SUCCESS;
}
