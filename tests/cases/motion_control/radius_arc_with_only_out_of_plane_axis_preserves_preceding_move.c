#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("G2Z1R1", Status_GcodeNoAxisWordsInPlane);
    return EXIT_SUCCESS;
}
