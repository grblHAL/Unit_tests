#include "support/wall_host.h"
#include "check.h"

int main(void)
{
    prepare_wall();
    coord_data_t start = {.x = 125, .y = 125}, target = {.x = 106, .y = 75};
    plan_line_data_t data = {0};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    grbl.on_jog_cancel(STATE_JOG);
    CHECK(kinematics.segment_line(&target, &start, &data, false) == NULL);
    return EXIT_SUCCESS;
}
