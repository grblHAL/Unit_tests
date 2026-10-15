#include "support/motion_program_host.h"
#if N_AXIS != 7
#error This case requires seven configured axes
#endif
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G1X1Y2Z3A4B5C6U7F120");
    execute_motion_program();
    const int32_t expected[] = {80, 160, 240, 320, 400, 480, 560};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == expected[axis]);
        CHECK(physical_position[axis] == expected[axis]);
        CHECK(axis_pulses[axis] == (unsigned)expected[axis]);
    }
    return EXIT_SUCCESS;
}
