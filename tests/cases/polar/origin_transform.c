#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "check.h"
void polar_init(void);
int main(void)
{
    engine_prepare();
    polar_init();
    coord_data_t input = {0}, result;
    kinematics.transform_from_cartesian(&result, &input);
    NEAR(result.x, 0);
    NEAR(result.y, 0);
    NEAR(result.z, 0);
    return EXIT_SUCCESS;
}
