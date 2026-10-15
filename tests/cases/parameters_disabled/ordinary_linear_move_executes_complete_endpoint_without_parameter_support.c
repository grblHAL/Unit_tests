#include "support/motion_program_host.h"
#if NGC_PARAMETERS_ENABLE || NGC_EXPRESSIONS_ENABLE
#error This case requires the parameters-disabled configuration
#endif
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G21G90G1X1Y2F120");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 80 && sys.position[Y_AXIS] == 160);
    CHECK(physical_position[X_AXIS] == 80 && physical_position[Y_AXIS] == 160);
    CHECK(axis_pulses[X_AXIS] == 80 && axis_pulses[Y_AXIS] == 160);
    return EXIT_SUCCESS;
}
