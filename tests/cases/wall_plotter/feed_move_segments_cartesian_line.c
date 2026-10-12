#include "support/wall_host.h"
#include "check.h"

int main(void)
{
    prepare_wall();
    coord_data_t start = {.x = 125, .y = 125}, target = {.x = 106, .y = 75};
    plan_line_data_t data = {0};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    for(unsigned segment = 1; segment <= 3; segment++) {
        coord_data_t *result = kinematics.segment_line(&target, &start, &data, false);
        CHECK(result != NULL);
        float x = 100 + segment * 2;
        CHECK(fabsf(result->x - hypotf(x, 75)) < .0001f);
        CHECK(fabsf(result->y - hypotf(200 - x, 75)) < .0001f);
    }
    CHECK(kinematics.segment_line(&target, &start, &data, false) == NULL);
    return EXIT_SUCCESS;
}
