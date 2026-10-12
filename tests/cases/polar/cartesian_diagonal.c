#include "support/engine_host.h"
#include "kinematics/interface.h"
#include "check.h"
void polar_init(void);
int main(void)
{
    engine_prepare();
    polar_init();
    coord_data_t input = {.x = 3, .y = 4}, result;
    kinematics.transform_from_cartesian(&result, &input);
    NEAR(result.x, 5);
    CHECK(fabsf(result.y - 53.1301f) < .0001f);
    return EXIT_SUCCESS;
}
