#include "support/wall_host.h"

int main(void)
{
    prepare_wall();
    coord_data_t start = {.x = 125, .y = 125}, target = {.x = 106, .y = 75};
    plan_line_data_t data = {0};
    CHECK(kinematics.segment_line(&target, &start, &data, true));
    grbl.on_jog_cancel(STATE_JOG);
    CHECK(kinematics.segment_line(&target, &start, &data, false) == NULL);
    CHECK(kinematics.segment_line(&target, &start, &data, true));
    for(unsigned i = 1; i <= 3; i++) CHECK(kinematics.segment_line(&target, &start, &data, false));
    CHECK(kinematics.segment_line(&target, &start, &data, false) == NULL);
    return EXIT_SUCCESS;
}
