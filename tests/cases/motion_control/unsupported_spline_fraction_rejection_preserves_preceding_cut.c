#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G5.2X2Y1I1J1", Status_GcodeUnsupportedCommand);
    return EXIT_SUCCESS;
}
