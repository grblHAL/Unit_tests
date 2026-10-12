#include "support/engine_host.h"
#include "report.h"
#include "check.h"

int main(void)
{
    engine_prepare();
    int32_t steps[N_AXIS] = {800, -400, 80};
    float position[N_AXIS];
    settings.axis[X_AXIS].steps_per_mm = 80;
    settings.axis[Y_AXIS].steps_per_mm = 100;
    settings.axis[Z_AXIS].steps_per_mm = 40;
    system_convert_array_steps_to_mpos(position, steps);
    NEAR(position[X_AXIS], 10);
    NEAR(position[Y_AXIS], -4);
    NEAR(position[Z_AXIS], 2);
    return EXIT_SUCCESS;
}
