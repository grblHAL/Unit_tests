#include "support/spline_program_host.h"
int main(void)
{
    /* Cubic (0,0), (0,1), (1,0), (1,1): t=1/4 gives x=5/32,y=7/16. */
    prepare_spline_program(318);
    queue_motion_program("G20G5X1Y1I0J1P0Q-1F4");
    finish_spline_program(2032, 2032, 889);
    CHECK(gc_state.modal.units_imperial);
    NEAR(gc_state.modal.spline_pq[Y_AXIS], -25.4f);
    return EXIT_SUCCESS;
}
