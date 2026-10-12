#include "support/delta_host.h"
#include "check.h"

int main(void)
{
    prepare_delta();
    coord_data_t target = {.z = -300}, start;
    kinematics.transform_from_cartesian(&start, &target);
    target.x = 1;
    plan_line_data_t data = {.condition = {.target_validated = true, .target_valid = true}};
    CHECK(kinematics.segment_line(&target, &start, &data, true) != NULL);
    grbl.on_jog_cancel(STATE_JOG);
    CHECK(kinematics.segment_line(&target, &start, &data, false) == NULL);
    return EXIT_SUCCESS;
}
