#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G2X2Y0R0.4999F100", Status_GcodeArcRadiusError);
    return EXIT_SUCCESS;
}
