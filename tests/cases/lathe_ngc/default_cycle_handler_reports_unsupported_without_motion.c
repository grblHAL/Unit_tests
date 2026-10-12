#include "support/css_host.h"
#include "motion_control.h"
#include "check.h"

int main(void)
{
    prepare_css_parser(true);
    plan_line_data_t data; plan_data_init(&data);
    coord_data_t position = {.x = 10, .z = 20};
    lathe_cycle_arguments_t args = {.motion = MotionMode_LatheFinishing};
    CHECK(mc_lathe_cycle(&data, &position, 7, &args) == Status_GcodeUnsupportedCommand);
    NEAR(position.x, 10); NEAR(position.z, 20); CHECK(plan_get_current_block() == NULL);
    return EXIT_SUCCESS;
}
