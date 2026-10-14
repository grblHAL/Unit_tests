#include "support/spline_program_host.h"
int main(void)
{
    /* Quadratic (0,0), (0,1), (1,1): t=1/2 gives x=1/4,y=3/4. */
    prepare_spline_program(508);
    queue_motion_program("G20G5.1X1Y1I0J1F4");
    finish_spline_program(2032, 2032, 1524);
    CHECK(gc_state.modal.units_imperial);
    return EXIT_SUCCESS;
}
