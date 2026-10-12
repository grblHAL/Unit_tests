#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    settings.axis[3].steps_per_mm = 81;
    mpos_t steps = {.values = {160, -240, 320, -243}};
    coord_data_t output;
    CHECK(kinematics.transform_steps_to_cartesian(&output, &steps) == &output);
    NEAR(output.values[0], 2);
    NEAR(output.values[1], -3);
    NEAR(output.values[2], 4);
    NEAR(output.values[3], -3);
    return EXIT_SUCCESS;
}
