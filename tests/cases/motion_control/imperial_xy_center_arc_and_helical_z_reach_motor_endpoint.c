#include "support/motion_program_host.h"
int main(void)
{
    prepare_motion_program();
    queue_motion_program("G20G17G3X0.125Y0.125Z0.0625J0.125F4");
    execute_motion_program();
    const int32_t expected[N_AXIS] = {254, 254, 127};
    for(unsigned axis = 0; axis < N_AXIS; axis++) {
        CHECK(sys.position[axis] == expected[axis]);
        CHECK(physical_position[axis] == expected[axis]);
        CHECK(axis_pulses[axis] == (unsigned)expected[axis]);
    }
    CHECK(gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
