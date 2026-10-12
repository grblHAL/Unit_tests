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
    coord_data_t input = {.x = 10, .y = 3, .z = -2}, output;
    CHECK(kinematics.transform_from_cartesian(&output, &input) == &output);
    NEAR(output.x, 13);
    NEAR(output.y, 7);
    NEAR(output.z, -2);
    return EXIT_SUCCESS;
}
