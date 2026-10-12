#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "check.h"
void polar_init(void);
int main(void)
{
    engine_prepare();
    polar_init();
    mpos_t steps = {.values = {800, 7200, 240}};
    coord_data_t result;
    kinematics.transform_steps_to_cartesian(&result, &steps);
    NEAR(result.x, 0);
    NEAR(result.y, 10);
    NEAR(result.z, 3);
    return EXIT_SUCCESS;
}
