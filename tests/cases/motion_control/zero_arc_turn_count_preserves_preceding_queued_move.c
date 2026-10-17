#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G2X2Y1I1P0", Status_GcodeValueOutOfRange);
    return EXIT_SUCCESS;
}
