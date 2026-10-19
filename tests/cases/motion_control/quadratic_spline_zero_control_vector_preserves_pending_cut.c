#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G5.1X3Y1I0J0F100", Status_GcodeValueOutOfRange);
    CHECK(gc_state.modal.plane_select == PlaneSelect_XY);
    return EXIT_SUCCESS;
}
