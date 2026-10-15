#include "support/motion_program_host.h"
#include "support/named_parameter_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(!settings.flags.report_inches);
    queue_motion_program("G20G1U1F1");
    execute_motion_program();
    CHECK(sys.position[U_AXIS] == 2032 && physical_position[U_AXIS] == 2032);
    CHECK(axis_pulses[U_AXIS] == 2032);
    NEAR(read_named_parameter("_u"), 1);
    NEAR(read_named_parameter("_abs_u"), 1);
    CHECK(!settings.flags.report_inches);
    for(unsigned axis = 0; axis < U_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
