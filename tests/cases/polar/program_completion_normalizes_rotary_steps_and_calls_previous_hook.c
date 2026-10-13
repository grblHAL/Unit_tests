#include "support/polar_segment_host.h"

int main(void)
{
    prepare_polar_segments();
    gc_state.position[X_AXIS] = 0;
    gc_state.position[Y_AXIS] = 10;
    sys.position[Y_AXIS] = 450 * settings.axis[Y_AXIS].steps_per_mm;
    grbl.on_program_completed(ProgramFlow_CompletedM30, true);
    CHECK(sys.position[Y_AXIS] == 90 * settings.axis[Y_AXIS].steps_per_mm);
    CHECK(polar_previous_completion_calls == 1);
    CHECK(polar_completion == ProgramFlow_CompletedM30 && polar_completion_check);
    NEAR(plan_get_position()[Y_AXIS], 90);
    return EXIT_SUCCESS;
}
