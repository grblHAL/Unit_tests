#include "support/motion_program_host.h"
#if NGC_PARAMETERS_ENABLE || NGC_EXPRESSIONS_ENABLE
#error This case requires the parameters-disabled configuration
#endif
int main(void)
{
    prepare_motion_program();
    char offset[] = "G92X-1";
    CHECK(gc_execute_block(offset) == Status_OK);
    queue_motion_program("G1X1F120");
    execute_motion_program();
    CHECK(sys.position[X_AXIS] == 160);
    CHECK(physical_position[X_AXIS] == 160 && axis_pulses[X_AXIS] == 160);
    CHECK(physical_position[Y_AXIS] == 0 && physical_position[Z_AXIS] == 0);
    return EXIT_SUCCESS;
}
