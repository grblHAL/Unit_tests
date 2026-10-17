#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G93G1X2", Status_GcodeUndefinedFeedRate);
    return EXIT_SUCCESS;
}
