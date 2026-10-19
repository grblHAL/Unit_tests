#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("N10000001G1X2", Status_GcodeInvalidLineNumber);
    return EXIT_SUCCESS;
}
