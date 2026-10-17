#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G20G91G10L2P1G33Z-1K1", Status_GcodeAxisCommandConflict);
    return EXIT_SUCCESS;
}
