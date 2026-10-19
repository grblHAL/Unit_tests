#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G92.4X2", Status_GcodeUnsupportedCommand);
    return EXIT_SUCCESS;
}
