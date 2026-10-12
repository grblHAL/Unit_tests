#include "support/wall_host.h"
#include "check.h"

int main(void)
{
    prepare_wall();
    coord_data_t start = {.x = 125, .y = 125}, target = {.x = 0, .y = 150};
    plan_line_data_t data = {.condition = {.rapid_motion = true}};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    coord_data_t *result = kinematics.segment_line(&target, &start, &data, false);
    CHECK(result != NULL);
    NEAR(result->x, 150);
    NEAR(result->y, 250);
    CHECK(kinematics.segment_line(&target, &start, &data, false) == NULL);
    return EXIT_SUCCESS;
}
