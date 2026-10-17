#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G93G2X2Y1I1", Status_GcodeUndefinedFeedRate);
    return EXIT_SUCCESS;
}
