#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "check.h"
void polar_init(void);
int main(void)
{
    engine_prepare();
    polar_init();
    coord_data_t input = {.x = 10, .y = 0, .z = 3}, result;
    CHECK(kinematics.transform_from_cartesian(&result, &input) == &result);
    NEAR(result.x, 10);
    NEAR(result.y, 0);
    NEAR(result.z, 3);
    return EXIT_SUCCESS;
}
