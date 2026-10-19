#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G81X2Z-1R1L1.5F100", Status_GcodeCommandValueNotInteger);
    return EXIT_SUCCESS;
}
