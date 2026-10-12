#include "support/delta_host.h"
#include "check.h"

int main(void)
{
    prepare_delta();
    coord_data_t input = {.z = -300}, result;
    kinematics.transform_from_cartesian(&result, &input);
    CHECK(isfinite(result.x));
    NEAR(result.x, result.y);
    NEAR(result.x, result.z);
    return EXIT_SUCCESS;
}
