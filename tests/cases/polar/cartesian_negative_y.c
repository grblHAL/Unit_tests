#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "check.h"
void polar_init(void);
int main(void)
{
    engine_prepare();
    polar_init();
    coord_data_t input = {.x = 0, .y = -10}, result;
    kinematics.transform_from_cartesian(&result, &input);
    NEAR(result.x, 10);
    NEAR(result.y, -90);
    return EXIT_SUCCESS;
}
