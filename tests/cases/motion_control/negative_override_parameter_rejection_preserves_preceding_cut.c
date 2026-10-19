#include "support/queued_motion_rejection_host.h"
int main(void)
{
    reject_without_losing_queued_motion("M50P-1", Status_NegativeValue);
    return EXIT_SUCCESS;
}
