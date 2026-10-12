#include "support/rtcp_host.h"
#include "check.h"

int main(void)
{
    prepare_rtcp();
    zero_rtcp_centers();
    rtcp_command(851);
    coord_data_t target = {.x = 1, .y = 2, .z = 3}, position = {0};
    plan_line_data_t data = {0};
    CHECK(kinematics.segment_line(&target, &position, &data, true) != NULL);
    coord_data_t *result = kinematics.segment_line(&target, &position, &data, false);
    CHECK(result != NULL);
    NEAR(result->x, 1);
    NEAR(result->y, 2);
    NEAR(result->z, 3);
    CHECK(kinematics.segment_line(&target, &position, &data, false) == NULL);
    return EXIT_SUCCESS;
}
