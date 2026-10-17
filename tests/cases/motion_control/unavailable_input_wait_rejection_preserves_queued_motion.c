#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G20G91M66P0L0G1X10F1", Status_GcodeUnsupportedCommand);
    return EXIT_SUCCESS;
}
