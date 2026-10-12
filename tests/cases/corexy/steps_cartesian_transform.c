#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "machine_limits.h"
#include "check.h"
void corexy_init(void);
int main(void)
{
    engine_prepare();
    limits_init();
    corexy_init();
    mpos_t steps = {.values = {1040, 560, -160}};
    coord_data_t output;
    CHECK(kinematics.transform_steps_to_cartesian(&output, &steps) == &output);
    NEAR(output.x, 10);
    NEAR(output.y, 3);
    NEAR(output.z, -2);
    return EXIT_SUCCESS;
}
