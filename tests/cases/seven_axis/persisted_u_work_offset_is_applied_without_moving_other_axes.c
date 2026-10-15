#include "support/motion_program_host.h"
#include "support/named_parameter_host.h"
int main(void)
{
    prepare_motion_program();
    CHECK(named_parameter_block("G10L2P2U2") == Status_OK);
    CHECK(named_parameter_block("G55") == Status_OK);
    queue_motion_program("G1U1F100");
    execute_motion_program();
    CHECK(sys.position[U_AXIS] == 240 && physical_position[U_AXIS] == 240);
    CHECK(axis_pulses[U_AXIS] == 240);
    NEAR(read_named_parameter("_u"), 1);
    NEAR(read_named_parameter("_abs_u"), 3);
    for(unsigned axis = 0; axis < U_AXIS; axis++) CHECK(axis_pulses[axis] == 0);
    return EXIT_SUCCESS;
}
