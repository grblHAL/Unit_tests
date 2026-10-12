#include "support/ganging_host.h"
#include "check.h"

int main(void)
{
    prepare_ganging();
    coord_data_t input = {.values = {2, -3, 4, 99}}, output;
    CHECK(kinematics.transform_from_cartesian(&output, &input) == &output);
    NEAR(output.values[0], 2);
    NEAR(output.values[1], -3);
    NEAR(output.values[2], 4);
    NEAR(output.values[3], -3);
    NEAR(input.values[3], 99);
    return EXIT_SUCCESS;
}
